/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/22 13:51:45 by lothieve         ###   ########.fr       */
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

std::map<int, Client*>	Channel::getClientsMap() {
	return this->_clients;
}

string					Channel::getClientsList() {
	string	ret("");
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		if (isOperator(it->second->getNickname()))
			ret += '@' + it->second->getNickname() + " ";
		else
			ret += it->second->getNickname() + " ";
	}
	return ret;
}

string					Channel::getClientsListOut() {
	string ret("");
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		if (!(*it).second->isInvisible()) {
			if (isOperator(it->second->getNickname()))
				ret += '@' + it->second->getNickname() + " ";
			else
				ret += it->second->getNickname() + " ";
		}
	}
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

bool					Channel::isEmpty() const {return _clients.empty();}

bool					Channel::isClient(Client& client) {
	return this->_clients.find(client.getSocket()) != this->_clients.end();
}

bool					Channel::isInvited(string client) {
	for (std::vector<Client*>::iterator it = this->_invit.begin(); it != this->_invit.end(); it++)
		if ((*it)->getNickname() == client)
			return true;
	return false;
}

bool					Channel::isVerbose(string client) {
	for (std::vector<Client*>::iterator it = this->_verbose.begin(); it != this->_verbose.end(); it++)
		if ((*it)->getNickname() == client)
			return true;
	return false;
}

bool					Channel::isModerate() const {
	return this->_mode.find('m') != string::npos ? true : false;
}

bool					Channel::isSecret() const {
	return this->_mode.find('s') != string::npos ? true : false;
}

bool					Channel::isPrivate() const {
	return this->_mode.find('p') != string::npos ? true : false;
}

void					Channel::addClient(Client& client) {
	this->_clients[client.getSocket()] = &client;
}

void					Channel::addOperator(Client& client) {_operators.push_back(&client);}

void					Channel::removeOperator(Client &client)
{
	std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), &client);
    if (it != _operators.end())
        _operators.erase(it);
}

void					Channel::removeVerbose(Client &client)
{
	std::vector<Client*>::iterator it = std::find(_verbose.begin(), _verbose.end(), &client);
    if (it != _verbose.end())
        _verbose.erase(it);
}

void                	Channel::removeClient(Client& client) {_clients.erase(client.getSocket());}
void                	Channel::addInvit(Client& client) {_invit.push_back(&client);}
void					Channel::addVerbose(Client &client) {_verbose.push_back(&client);}
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
