/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/26 14:51:31 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(): _name(""), _connectionManager(ConnectionManager::getInstance()), _ping(std::time(NULL)) {};
void                Server::acceptClient() {
	int         client;
	sockaddr_in addr;
	socklen_t   len = sizeof(addr);
	if ((client = accept(_sock, (sockaddr*)&addr, &len)) < 0) {
		std::cerr << "Accept failed" << std::endl;
		exit(1);
	}
	_clients[client] = new Client(client, addr);
	std::cout << addr.sin_addr.s_addr << std::endl;
	_fds.push_back(pollfd());
	_fds.back().fd = client;
	_fds.back().events = POLLIN;
};

void                Server::setPort(int port) {_port = port;}
void                Server::setPassword(char* password) {_password.assign(password);};

void                Server::init(int port, char *pw) {
	int         opt = 1;
	sockaddr_in addr;

	setPort(port);
	_connectionManager->setPort(port);
	setPassword(pw);
	if (!(_sock = socket(AF_INET, SOCK_STREAM, 0))) {
		std::cerr << "Socket failed" << std::endl;
		exit(1);
	}
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "Setsockopt failed" << std::endl;
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(_port);
	if (bind(_sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
		std::cerr << "Bind failed" << std::endl;
		exit(1);
	}
	if (listen(_sock, 10) < 0) {
		std::cerr << "Listen failed" << std::endl;
		exit(1);
	}
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) < 0) {
		std::cerr << "Fcntl failed" << std::endl;
		exit(1);
	}
	_fds.push_back(pollfd());
	_fds.back().fd = _sock;
	_fds.back().events = POLLIN;
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
	return _channels[name];
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
void                    Server::erraseClient(Client client) {
	// TODO
	client.setState(DEBUG);
};
void                    Server::erraseChannel(Channel channel) {
	// TODO
	std::cout << "Channel errased" << std::endl;
	(void)channel;
	return;
};

void                    Server::run() {
	std::vector<Client*>    clients_list = getClients();
	while(1) {
		if (poll(_fds.data(), _fds.size(), -1) < 0) {
			std::cerr << "Poll failed" << std::endl;
			exit(1);
		}
		if (std::time(NULL) - _ping > 4)
			sendPing();
		if (_fds[0].revents == POLLIN) acceptClient();
		else
			for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); it++)
				if ((*it).revents == POLLIN)
					_clients[(*it).fd]->receiveMessage(this);
		for (std::vector<Client*>::iterator it = clients_list.begin(); it != clients_list.end(); it++)
			if ((*it)->getStats() == NONE)
				erraseClient(*(*it));
		clients_list = getClients();
		for (std::vector<Client*>::iterator it = clients_list.begin(); it != clients_list.end(); it++)
			(*it)->sendMessage();
	}
};
