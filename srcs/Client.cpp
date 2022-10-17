/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/17 22:15:36 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"

Client::Client(int sock, sockaddr_in addr):_state(CHECKPASS), _sock(sock), _quitMessage("has quit"), _ping(std::time(NULL)) {
	_addr = inet_ntoa(addr.sin_addr);
	_cmdmgr = CommandManager::getInstance();
};

Client::~Client() {
    close(_sock);
};
int     	Client::getSocket() const {
    return _sock;
};
string 		Client::getNickname() const {
    return _nickname;
};
string 		Client::getUsername() const {
    return _username;
};
string		Client::getRealname() const {
	return _realname;
};
string		Client::getMode() const {
	return _mode;
};
string		Client::getAddr() const {
	return _addr;
};
e_state		Client::getStats() const {
	return _state;
};
string		Client::getQuitMessage() const {
	return _quitMessage;
};
void    	Client::setNickname(string nickname) {
    _nickname = nickname;
};
void    	Client::setUsername(string username) {
    _username = username;
};

void		Client::setRealName(string realname) {
	_realname = realname;
};
void		Client::setState(e_state mode) {
	_state = mode;
};
void		Client::setPing(time_t ping) {
	_ping = ping;
};

void		Client::setMode(string mode)
{
	_mode = mode;
};
void		Client::setQuitMessage(string message) {
	this->_quitMessage = message;
};

string	Client::stateMsg() {
	string	state = "";
	if (_state == CONNECTED) {
		state = _nickname;
		if (!_addr.empty()) {
			if (!_username.empty())
				state += "!" + _username;
			state += "@" + _addr;
		}
	}
	return state + " ";
};

void    Client::receiveMessage() {
	std::string	command;
	std::string packet;
    size_t  	pos = 0;

	try {packet = ConnectionManager::getInstance()->receivePacket(_sock);}
	catch (ConnectionManager::ConnectException &e) {return ;}
	std::cout << packet;
	while ((pos = packet.find("\r\n")) != std::string::npos) {
    	command = packet.substr(0, pos);
		packet.erase(0, pos + 2);
		if (command.empty()) continue;
		try {CommandManager::getInstance()->execute(command, *this);}
		catch (CommandManager::CommandException e) {}
    }
	while ((pos = packet.find("\n")) != std::string::npos) {
    	command = packet.substr(0, pos);
		packet.erase(0, pos + 1);
		if (command.empty()) continue;
		try {CommandManager::getInstance()->execute(command, *this);}
		catch (CommandManager::CommandException e) {}
    }
};

void	Client::writePrefixMsg(string message) {
	writeMessage(":" + stateMsg() + message);
};

void	Client::writePrefixMsg(Client& client, string message) {
	client.writeMessage(":" + stateMsg() + message);
};

void	Client::writePrefixMsg(int code, string message) {
	std::stringstream	ss;
	string				str;
	ss << code;
	str = ss.str();
	if (str.length() < 3)
		str = str.length() == 2 ? "0" : "00" + str;
	writeMessage(":" + stateMsg() + str + " " + this->_nickname + message);
};

void	Client::writePrefixMsg(int code, Client &client, string message) {
	client.writePrefixMsg(code, message);
};

void    Client::writeMessage(string message) {
	_packets.push_back(message);
};

bool		Client::isDisconnected() const {char buf; return recv(_sock, &buf, 1, MSG_PEEK | MSG_DONTWAIT);}

void    Client::sendMessage() {
    string packet;
    if (_packets.empty()) return;
	for (std::vector<string>::iterator it = _packets.begin(); it != _packets.end(); it++)
		packet += *it + "\r\n";
	this->_packets.clear();
	if (!packet.empty())
		send(this->_sock, packet.c_str(), packet.size(), 0);
};

void    Client::registerClient() {
	Context context;

	context.client = this;
	context.channel = 0;
    _cmdmgr->sendReply(1, context);
	_cmdmgr->sendReply(2, context);
	_cmdmgr->sendReply(3, context);
	_cmdmgr->sendReply(4, context);
	LUSERS(context, 0);
	MOTD(context, 0);
}
