/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/26 13:37:40 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"
#include "Server.hpp"
#include "Commands.hpp"

void	PASS(Commands*);
void	NICK(Commands*);
void	USER(Commands*);
void	TIME(Commands*);
void	MOTD(Commands*);
void	LUSERS(Commands*);
void	PING(Commands*);
void	PONG(Commands*);
void	MODE(Commands*);
void	JOIN(Commands*);

Client::Client(int sock, sockaddr_in addr):_state(CHECKPASS), _sock(sock), _userMode("w"), _ping(std::time(NULL)) {
	_listCommands["PASS"] = PASS;
	_listCommands["NICK"] = NICK;
	_listCommands["USER"] = USER;
	_listCommands["TIME"] = TIME;
	_listCommands["MOTD"] = MOTD;
	_listCommands["LUSERS"] = LUSERS;
	_listCommands["PING"] = PING;
	_listCommands["PONG"] = PONG;
	_listCommands["MODE"] = MODE;
	_listCommands["JOIN"] = JOIN;
	_addr = inet_ntoa(addr.sin_addr);
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
std::string	Client::getUsermode() const {
	return _userMode;
};
std::string	Client::getAddr() const {
	return _addr;
};
e_state		Client::getStats() const {
	return _state;
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
    bytes = recv(_sock, buff, 1024, 0);
	buff[bytes] = '\0';
    if (bytes < 1) {
		if (bytes == 0)
			_state = NONE;
		return ;
	}
    _buff += buff;
	std::cout << buff << std::endl;
    while ((pos = _buff.find("\r\n")) != std::string::npos) {
    	msg = _buff.substr(0, pos);
		_buff.erase(0, pos + 2);
		if (!msg.size())
			continue;
		_commands.push_back(new Commands(this, serv, msg));
    }
    packetsHandler();
};

void    Client::writeMessage(std::string message) {
	_packets.push_back(":" + stateMsg() + " " + message);
};
void    Client::sendMessage() {
    std::string packet;
    if (!_packets.empty()) {
        for (std::vector<std::string>::iterator it = _packets.begin(); it != _packets.end(); it++)
            packet += *it + "\r\n";
        _packets.clear();
        if (packet.size())
            send(_sock, packet.c_str(), packet.size(), 0);
    }
};
void    Client::registerClient(Commands* commands) {
    writeMessage(commands->sendRep(1));
	writeMessage(commands->sendRep(2));
	writeMessage(commands->sendRep(3));
	writeMessage(commands->sendRep(4));
	LUSERS(commands);
	MOTD(commands);
};
