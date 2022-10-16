/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/16 15:01:19 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(string &name, Client *creator) : _name(name), _topic(""), _creationTime(std::time(NULL)) {
	ClientMode elem(creator, "");
	_clientsWhat[creator->getSocket()] = elem;
}

Channel::Channel () : _creationTime(std::time(NULL)) {}

void                	Channel::addClient(Client *client) {
	ClientMode elem(client, "");
	_clientsWhat[client->getSocket()] = elem;
}

Client*					Channel::getClient(string name) {
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->second->getNickname() == name)
			return it->second;
	}
	return NULL;
}

std::vector<Client*>	Channel::getClients() {
    std::vector<Client*>	clients;
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		clients.push_back(it->second);
	return clients;
}

std::vector<Client *> Channel::getBanlist()
{
	std::vector<Client*>	banned;
	for (std::vector<Client*>::iterator it = this->_banlist.begin(); it != this->_banlist.end(); it++)
		banned.push_back(*it);
	return banned;
}

std::map<int, Client*>	Channel::getClientsMap() {
	return this->_clients;
}

string					Channel::getClientsList() {
	string	ret("");
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		ret += it->second->getNickname() + " ";
	return ret;
}
size_t					Channel::getVisiblesNbr() {
	size_t	ret = 0;
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		++ret;
	return ret;
}
bool					Channel::isOperator(string client) {
	bool	ret = false;
	for (std::vector<Client*>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
		if ((*it)->getNickname() == client)
			ret = true;
	return ret;
}

bool					Channel::isBanned(string client)
{
	bool ret = false;
	for (std::vector<Client*>::iterator it = this->_banlist.begin(); it != this->_banlist.end(); it++)
		if ((*it)->getNickname() == client)
			ret = true;
	return (ret);
}

bool					Channel::isEmpty() const {return _clients.empty();}

bool					Channel::isClient(Client& client) {
	return this->_clients.find(client.getSocket()) != this->_clients.end();
}

void					Channel::addClient(Client& client) {
	this->_clients[client.getSocket()] = &client;
}

void					Channel::addOperator(Client& client) {_operators.push_back(&client);}
void					Channel::addBanned(Client &client) {_banlist.push_back(&client);}
void                	Channel::removeClient(Client& client) {_clients.erase(client.getSocket());}
void                	Channel::addInvit(Client& client) {_invit.push_back(&client);}
void                	Channel::removeInvit(Client& client) {
    std::vector<Client*>::iterator it = std::find(_invit.begin(), _invit.end(), &client);
    if (it != _invit.end()) {
        _invit.erase(it);
    }
}

void                	Channel::broadcastMessage(Client& client, string message) {
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		client.writePrefixMsg(*it->second, " " + message);
};

bool					Channel::isOn(int socket) {return _clients.find(socket) != _clients.end();}
void           			Channel::setName(string &name) {_name = name;}
void           			Channel::setTopic(string &topic) {_topic = topic;}
void           			Channel::setMode(string &mode) {_mode = mode;}
void           			Channel::setPassword(string password) {_password = password;}
const string         			&Channel::getName() const {return _name;}
const string         			&Channel::getTopic() const {return _topic;}
const string         			&Channel::getMode() const {return _mode;}
const string         			&Channel::getPassword() const {return _password;}
time_t							Channel::getCreationTime() const {return _creationTime;}
