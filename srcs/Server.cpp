/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/22 14:07:09 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cstdio>
#include <algorithm>

Server	*Server::_instance = 0;
Server::Server(): _name(""), _connectionManager(ConnectionManager::getInstance()), _ping(std::time(NULL)), _die(false) {};

Server				*Server::getInstance() {
	if (!_instance) _instance =  new Server();
	return _instance;
}

void                Server::acceptClient() {
	int         clientFd;
	sockaddr_in addr;
	socklen_t   len = sizeof(addr);

	clientFd = accept(_connectionManager->getMainSock(), (sockaddr*)&addr, &len);
	if (clientFd  < 0) throw ConnectionManager::ConnectException("Accept failed");
	_clients[clientFd] = new Client(clientFd, addr);
	_connectionManager->addClient(clientFd);
};

void                Server::setPassword(char* password) {_password.assign(password);};

void                Server::init(int port, char *pw) {
	_connectionManager->init(port);
	setPassword(pw);
	_serverTime = std::time(NULL);
};

std::string			Server::getStartTime()
{
	return (std::ctime(&_serverTime));
}

Client*             Server::getClient(std::string nickName) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((*it).second->getNickname() == nickName)
			return (*it).second;
	return NULL;
};
std::vector<Client*>    Server::getClients() {
	std::vector<Client*>    clients;
	clients.reserve(_clients.size());
	for (ClientIt it = _clients.begin(); it != _clients.end(); it++)
		clients.push_back(it->second);
	return clients;
};

Channel&                Server::getChannel(std::string name) {
	Channel&	channel =_channels[name];
	channel.setName(name);
    return channel;
};

std::vector<Channel*>   Server::getChannels() {
	std::vector<Channel*> channels;
	channels.reserve(_channels.size());
	for (ChanIt it = _channels.begin(); it != _channels.end(); it++)
		channels.push_back(&(*it).second);
	return channels;
};

void                    Server::sendPing() {
	std::stringstream	ss;
	ss << rand();
	_ping = std::time(NULL);
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((*it).second->getStats() == REGISTERED)
			(*it).second->writeMessage("PING " + ss.str());
};
void                    Server::erraseClient(Client& client) {
	std::vector<Client*>	clients;
	std::vector<Client*>	buff;
	std::string				message = "QUIT :" + client.getQuitMessage();
	buff.push_back(&client);
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		if ((*it).second.isClient(client)) {
			(*it).second.removeClient(client);
			clients = it->second.getClients();
			if (!clients.empty()) {
				for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
					if (std::find(buff.begin(), buff.end(), *it) == buff.end())
						buff.push_back(*it);
			}
		}
		if ((*it).second.isInvited(client.getNickname()))
			(*it).second.removeInvit(client);
		if ((*it).second.isVerbose(client.getNickname()))
			(*it).second.removeVerbose(client);
	}
	for (std::vector<Client*>::iterator it = buff.begin(); it != buff.end(); it++)
		client.writePrefixMsg(*(*it), message);
	this->_clients.erase(client.getSocket());
	delete &client;
};
void                    Server::erraseChannel(Channel channel) {
	_channels.erase(channel.getName());
};

void					Server::display() {
	std::cout << "\033[2J\033[1;1H" << std::flush;
	std::cout << "clients: " << std::endl;
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		std::cout << (*it).second->getNickname() << std::endl;
	std::cout << std::endl << "channels: " << std::endl;
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
		std::cout << (*it).second.getName() << std::endl;
};

bool					Server::isNickTaken(std::string nick) {
	for (ClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNickname() == nick)
			return true;
	return false;
}

void					Server::pruneClients() {
	
	for (ClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getStats() == NONE || it->second->isDisconnected()) {
			erraseClient(*it->second);
			return ;
		}
}

void					Server::killServ() {
	Channel *toErase = NULL;
	pruneClients();
	this->_die = true;
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
			if (it->second.isEmpty()) toErase = &it->second;
		if (toErase) erraseChannel(*toErase);
	exit(0);
}

void                    Server::run() {
	std::vector<Client*>    clients_list = getClients();
	int fd;

	for(;;) {
		Channel *toErase = NULL;
		fd = _connectionManager->waitForEvent();
		if (std::time(NULL) - _ping > 42) sendPing();
		if (fd == _connectionManager->getMainSock()) acceptClient();
		else _clients[fd]->receiveMessage();
		pruneClients();
		for (ClientIt it = _clients.begin(); it != _clients.end(); ++it)
			it->second->sendMessage();
		if (_channels.empty()) continue;
		for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
			if (it->second.isEmpty()) toErase = &it->second;
		if (toErase) erraseChannel(*toErase);
		if (this->_die)
			return;
	}
};

size_t					Server::getInvisNbr() const {
	size_t count = 0;
	for (ConstClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it).second->getStats() == REGISTERED && (*it).second->getMode().find('i') != std::string::npos) ++count;
	return count;
}

size_t					Server::getVisibleNbr() const {
	size_t count = 0;
	for (ConstClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it).second->getStats() == REGISTERED && (*it).second->getMode().find('i') == std::string::npos) ++count;
	return count;
}

size_t					Server::getOPNbr() const {
	size_t count = 0;
	for (ConstClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it).second->getStats() == REGISTERED && (*it).second->getMode().find('o') != std::string::npos) ++count;
	return count;
}

size_t					Server::getUnknbr() const {
	size_t count = 0;
	for (ConstClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it).second->getStats() != REGISTERED) ++count;
	return count;
}

Channel					&Server::findChannel(std::string name) {
	ChanIt it = _channels.find(name);
	if (it == _channels.end()) throw ChannelNotFoundException();
	return it->second;
}

Client					&Server::findClient(std::string name) {
	for (ClientIt it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNickname() == name) return *it->second;
	throw ClientNotFoundException();
}

size_t					Server::getUsrNbr() const {return _clients.size();}
size_t					Server::getChanNbr() const {return _channels.size();}
std::string				Server::getPassword() const {return _password;}
std::string				Server::getName() const {return _name;};
