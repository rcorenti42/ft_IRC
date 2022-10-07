/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/21 03:24:32               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   Channel.cpp                                                              */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(string &name, Client *creator) : _name(name), _topic("") {
	ClientMode elem(creator, "");
	_clientsWhat[creator->getSocket()] = elem;
}

Channel::Channel() {}

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

bool					Channel::isEmpty() const {return _clients.empty();}

bool					Channel::isClient(Client& client) {
	return this->_clients.find(client.getSocket()) != this->_clients.end();
}

void					Channel::addClient(Client& client) {
	this->_clients[client.getSocket()] = &client;
}

void					Channel::addOperator(Client& client) {_operators.push_back(&client);}
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
