/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/10 11:06:08 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"

void	PASS(Context &context, std::string *args);
void	NICK(Context &context, std::string *args);
void	USER(Context &context, std::string *args);
void	INFO(Context &context, std::string *args);
void	MOTD(Context &context, std::string *args);
void	LUSERS(Context &context, std::string *args);
void	PING(Context &context, std::string *args);
void	PONG(Context &context, std::string *args);
void	MODE(Context &context, std::string *args);
void	ISON(Context &context, std::string *args);
void	JOIN(Context &context, std::string *args);
void	PRIVMSG(Context &context, std::string *args);
void	NOTICE(Context &context, std::string *args);
void	PART(Context &context, std::string *args);
void	TOPIC(Context &context, std::string *args);
void	QUIT(Context &context, std::string *args);
void	OPER(Context &context, std::string *args);
void	VERSION(Context &context, std::string *args);
void	KICK(Context &context, std::string *args);

Client::Client(int sock, sockaddr_in addr):_state(CHECKPASS), _sock(sock), _mode("w"), _ping(std::time(NULL)) {
	_listCommands["INFO"] = INFO;
	_listCommands["PASS"] = PASS;
	_listCommands["NICK"] = NICK;
	_listCommands["USER"] = USER;
	_listCommands["MOTD"] = MOTD;
	_listCommands["LUSERS"] = LUSERS;
	_listCommands["PING"] = PING;
	_listCommands["PONG"] = PONG;
	_listCommands["MODE"] = MODE;
	_listCommands["JOIN"] = JOIN;
	_listCommands["ISON"] = ISON;
	_listCommands["PRIVMSG"] = PRIVMSG;
	_listCommands["NOTICE"] = NOTICE;
	_listCommands["PART"] = PART;
	_listCommands["TOPIC"] = TOPIC;
	_listCommands["QUIT"] = QUIT;
	_listCommands["OPER"] = OPER;
	_listCommands["VERSION"] = VERSION;
	_listCommands["KICK"] = KICK;
	_addr = inet_ntoa(addr.sin_addr);
	_cmdmgr = CommandManager::getInstance();
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
	return state + " ";
};

void    Client::receiveMessage() {
	std::string	command;
	std::string packet;
    size_t  	pos = 0;

	try {packet = ConnectionManager::getInstance()->receivePacket(_sock);}
	catch (ConnectionManager::ConnectException &e) {return ;}
	std::cout << packet << "================================\n";
	while ((pos = packet.find("\r\n")) != std::string::npos) {
    	command = packet.substr(0, pos);
		packet.erase(0, pos + 2);
		if (command.empty()) continue;
		try {CommandManager::getInstance()->execute(command, *this);}
		catch (CommandManager::CommandException e) {}
    }
};

void	Client::writePrefixMsg(std::string message) {
	writeMessage(":" + stateMsg() + message);
};

void	Client::writePrefixMsg(Client& client, std::string message) {
	client.writeMessage(":" + stateMsg() + message);
};

void	Client::writePrefixMsg(int code, std::string message) {
	std::stringstream	ss;
	std::string			str;
	ss << code;
	str = ss.str();
	if (str.length() < 3)
		str = str.length() == 2 ? "0" : "00" + str;
	writeMessage(":" + stateMsg() + str + " " + this->_nickname + message);
};

void	Client::writePrefixMsg(int code, Client &client, std::string message) {
	client.writePrefixMsg(code, message);
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

void    Client::registerClient() {
	Context context;

	context.client = this;
	context.channel = 0;
    writePrefixMsg(1, _cmdmgr->getReply(1, context));
	writePrefixMsg(2, _cmdmgr->getReply(2, context));
	writePrefixMsg(3, _cmdmgr->getReply(3, context));
	writePrefixMsg(4, _cmdmgr->getReply(4, context));
	LUSERS(context, 0);
	MOTD(context, 0);
}
