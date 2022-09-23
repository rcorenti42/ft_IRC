/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 03:24:52 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool                Server::validPort(char* port) {
    for (int i = 0; port[i]; i++)
        if (!isdigit(port[i]))
            return false;
    return true;
};
void                Server::acceptClient() {
    int         client;
    sockaddr_in addr;
    socklen_t   len = sizeof(addr);
    if ((client = accept(this->_sock, (sockaddr*)&addr, &len)) < 0) {
        std::cerr << "Accept failed" << std::endl;
        exit(1);
    }
    this->_clients[client] = new Client(client, addr);
    this->_fds.push_back(pollfd());
    this->_fds.back().fd = client;
    this->_fds.back().events = POLLIN;
};
void                Server::setPort(char* port) {
    std::stringstream   ss(port);
    if (!(ss >> this->_port) || !validPort(port)) {
        std::cerr << "Invalid port" << std::endl;
        exit(1);
    }
};
void                Server::setPassword(char* password) {
    this->_password.assign(password);
};
void                Server::init() {
    int         opt = 1;
    sockaddr_in addr;
    if (!(this->_sock = socket(AF_INET, SOCK_STREAM, 0))) {
        std::cerr << "Socket failed" << std::endl;
        exit(1);
    }
    if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed" << std::endl;
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(this->_port);
    if (bind(this->_sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        exit(1);
    }
    if (listen(this->_sock, 10) < 0) {
        std::cerr << "Listen failed" << std::endl;
        exit(1);
    }
    if (fcntl(this->_sock, F_SETFL, O_NONBLOCK) < 0) {
        std::cerr << "Fcntl failed" << std::endl;
        exit(1);
    }
    this->_fds.push_back(pollfd());
    this->_fds.back().fd = this->_sock;
    this->_fds.back().events = POLLIN;
};
Client*             Server::getClient(std::string nickName) {
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if ((*it).second->getNickname() == nickName)
			return (*it).second;
	return NULL;
};
std::vector<Client*>    Server::getClients() {
    std::vector<Client*>    clients;
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
        clients.push_back(it->second);
    return clients;
};
Channel&                Server::getChannel(std::string name) {
    return this->_channels[name];
};
std::vector<Channel*>   Server::getChannels() {
	std::vector<Channel*> channels;
	for (std::map<std::string, Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		channels.push_back(&(*it).second);
	return channels;
};

std::string				Server::getPassword() {
	return (this->_password);
}


time_t*            Server::getTime() {
    // TODO
    return this->_time;
};

std::string				Server::getName(){
	return this->_name;
}
void                    Server::sendPing() {
    // TODO
    std::cout << "Ping send" << std::endl;
    return;
};
void                    Server::erraseClient(Client client) {
    // TODO
	client.setState(NONE);
};
void                    Server::erraseChannel(Channel channel) {
    // TODO
    std::cout << "Channel errased" << std::endl;
    (void)channel;
    return;
};
void                    Server::run() {
    std::vector<Client*>    clients_list = getClients();
    if (poll(this->_fds.data(), this->_fds.size(), -1) < 0) {
        std::cerr << "Poll failed" << std::endl;
        exit(1);
    }
    if (this->_fds[0].revents == POLLIN)
        acceptClient();
    else
        for (std::vector<pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
            if ((*it).revents == POLLIN)
                this->_clients[(*it).fd]->receiveMessage(this);
    for (std::vector<Client*>::iterator it = clients_list.begin(); it != clients_list.end(); it++)
		if ((*it)->getStats() == NONE)
			erraseClient(*(*it));
	clients_list = getClients();
	for (std::vector<Client*>::iterator it = clients_list.begin(); it != clients_list.end(); it++)
        (*it)->sendMessage();
};
