/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/03 01:38:42 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"
#include "Server.hpp"
#include "Commands.hpp"

Client::Client(int sock, sockaddr_in addr):_state(CHECKPASS), _sock(sock), _ping(std::time(NULL)) {
	this->_listCommands["INFO"] = INFO;
	this->_listCommands["PASS"] = PASS;
	this->_listCommands["NICK"] = NICK;
	this->_listCommands["USER"] = USER;
	this->_listCommands["TIME"] = TIME;
	this->_listCommands["MOTD"] = MOTD;
	this->_listCommands["LUSERS"] = LUSERS;
	this->_listCommands["PING"] = PING;
	this->_listCommands["PONG"] = PONG;
	this->_listCommands["MODE"] = MODE;
	this->_listCommands["JOIN"] = JOIN;
	this->_listCommands["ISON"] = ISON;
	this->_listCommands["PRIVMSG"] = PRIVMSG;
	this->_listCommands["PART"] = PART;
	this->_listCommands["TOPIC"] = TOPIC;
	this->_listCommands["OPER"] = OPER;
	this->_listCommands["QUIT"] = QUIT;
	this->_addr = inet_ntoa(addr.sin_addr);
};
Client::~Client() {
    close(_sock);
};
int     Client::getSocket() const {
    return _sock;
};
std::string Client::getNickname() const {
    return _nickname;
};
std::string Client::getUsername() const {
    return _username;
};
std::string	Client::getRealname() const {
	return _realname;
};
std::string	Client::getMode() const {
	return _mode;
};
std::string	Client::getAddr() const {
	return _addr;
};
e_state		Client::getStats() const {
	return _state;
};
std::string	Client::getQuitMessage() const {
	return this->_quitMessage.empty() ? "has quit" : this->_quitMessage;
};
void    Client::setNickname(std::string nickname) {
    _nickname = nickname;
};
void    Client::setUsername(std::string username) {
    _username = username;
};

void	Client::setRealName(std::string realname) {
	_realname = realname;
};
void		Client::setState(e_state mode) {
	_state = mode;
};
void		Client::setPing(time_t ping) {
	_ping = ping;
};

void		Client::setMode(std::string mode)
{
	_mode = mode;
};
void		Client::setQuitMessage(std::string message) {
	this->_quitMessage = message;
};
std::string	Client::stateMsg() {
	std::string	state = "";
	if (_state == CONNECTED) {
		state = _nickname;
		if (!_addr.empty()) {
			if (!_username.empty())
				state += "!" + _username;
			state += "@" + _addr;
		}
	}
	return state;
};
void    Client::packetsHandler() {
	std::vector<Commands*>	commands;
	e_state					state = _state;
	if (_state != NONE) {
		for (std::vector<Commands*>::iterator it = _commands.begin(); it != _commands.end(); it++) {
			if (_state == CHECKPASS) {
				if ((*it)->getCommand() != "PASS")
					continue ;
			}
			else if (_state == REGISTERED)
				if ((*it)->getCommand() != "NICK" && (*it)->getCommand() != "USER")
					continue ;
			if (_listCommands.count((*it)->getCommand()))
				_listCommands[(*it)->getCommand()](*it);
			commands.push_back(*it);
		}
		for (std::vector<Commands*>::iterator it = commands.begin(); it != commands.end(); it++) {
			if (std::find(_commands.begin(), _commands.end(), *it) != _commands.end()) {
				_commands.erase(std::find(_commands.begin(), _commands.end(), *it));
				delete *it;
			}
		}
		if (_state == REGISTERED && !_nickname.empty())
			_state = CONNECTED;
		if (_state != state) {
			if (_state == CONNECTED)
				registerClient(*_commands.begin());
			packetsHandler();
		}
    }
};
void    Client::receiveMessage(Server* serv) {
    char    	buff[1025];
	std::string	msg;
    size_t  	bytes;
    size_t  	pos;
    bytes = recv(this->_sock, buff, 1024, 0);
	buff[bytes] = '\0';
    if (bytes < 1) {
		if (bytes == 0)
			this->_state = NONE;
		return ;
	}
    this->_buff += buff;
	std::cout << buff << std::endl;
	while ((pos = this->_buff.find("\r\n")) != std::string::npos) {
    	msg = this->_buff.substr(0, pos);
		this->_buff.erase(0, pos + 2);
		if (msg.empty())
			continue;
		this->_commands.push_back(new Commands(this, serv, msg));
    }
    packetsHandler();
};

void	Client::writePrefixMsg(Client& client, std::string message) {
	client.writeMessage(":" + stateMsg() + message);
};

void    Client::writeMessage(std::string message) {
	_packets.push_back(message);
};

void    Client::sendMessage() {
    std::string packet;
    if (!_packets.empty()) {
        for (std::vector<std::string>::iterator it = _packets.begin(); it != _packets.end(); it++)
            packet += *it + "\r\n";
        this->_packets.clear();
        if (!packet.empty())
            send(this->_sock, packet.c_str(), packet.size(), 0);
    }
};
void    Client::registerClient(Commands* commands) {
    writePrefixMsg(*this, commands->sendRep(1));
	writePrefixMsg(*this, commands->sendRep(2));
	writePrefixMsg(*this, commands->sendRep(3));
	writePrefixMsg(*this, commands->sendRep(4));
	LUSERS(commands);
	MOTD(commands);
};
