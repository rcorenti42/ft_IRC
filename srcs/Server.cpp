/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/02 17:24:30 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cstdio>

Server::Server(): _name(""), _connectionManager(ConnectionManager::getInstance()), _ping(std::time(NULL)) {};

void                Server::acceptClient() {
	int         clientFd;
	sockaddr_in addr;
	socklen_t   len = sizeof(addr);

	clientFd = accept(_connectionManager->getMainSock(), (sockaddr*)&addr, &len);
	if (clientFd  < 0) std::perror("accept");
	_clients[clientFd] = new Client(clientFd, addr);
	std::cout << clientFd << " -> " << _clients[clientFd] << std::endl;
	_connectionManager->addClient(clientFd);
};

void                Server::setPassword(char* password) {_password.assign(password);};

void                Server::init(int port, char *pw) {
	_connectionManager->init(port);
	setPassword(pw);
};

Client*             Server::getClient(std::string nickName) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((*it).second->getNickname() == nickName)
			return (*it).second;
	return NULL;
};
std::vector<Client*>    Server::getClients() {
	std::vector<Client*>    clients;
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		clients.push_back(it->second);
	return clients;
};
Channel&                Server::getChannel(std::string name) {
	Channel&	channel = this->_channels[name];
	channel.setName(name);
    return channel;
};
std::vector<Channel*>   Server::getChannels() {
	std::vector<Channel*> channels;
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
		channels.push_back(&(*it).second);
	return channels;
};
std::string				Server::getPassword() const {
	return (_password);
};
std::string				Server::getName() const {
	return _name;
};
void                    Server::sendPing() {
	_ping = std::time(NULL);
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((*it).second->getStats() == CONNECTED)
			(*it).second->writeMessage("PING 42");
};
void                    Server::erraseClient(Client& client) {
	this->_clients.erase(client.getSocket());
	delete &client;
};
void                    Server::erraseChannel(Channel channel) {
	this->_channels.erase(channel.getName());
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

void                    Server::run() {
	std::vector<Client*>    clients_list = getClients();
	int fd;

	while(1) {
		fd = _connectionManager->waitForEvent();
		if (std::time(NULL) - _ping > 42) sendPing();
		if (fd == _connectionManager->getMainSock()) acceptClient();
		else _clients[fd]->receiveMessage(this);
		for (std::vector<Client*>::iterator it = clients_list.begin(); it != clients_list.end(); it++)
			if ((*it)->getStats() == NONE)
				erraseClient(*(*it));
		clients_list = getClients();
		for (std::vector<Client*>::iterator it = clients_list.begin(); it != clients_list.end(); it++)
			(*it)->sendMessage();
		for (std::map<std::string, Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
			if (it->second.getClients().empty())
				erraseChannel(it->second);
		// display();
	}
};
