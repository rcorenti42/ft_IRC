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

Channel::Channel(string &name, Client &creator) : _name(name) {
	ClientMode elem(creator, "");
	_clients[creator.getSocket()] = elem;
}

Channel::Channel() {}

std::vector<Client> Channel::getClients() const {
    std::vector<Client> clients;
    clients.reserve(_clients.size());
    for (CliCstIt it = _clients.begin(); it != _clients.end(); ++it) clients.push_back(it->second.client);
    return clients;
}
void                Channel::addClient(Client& client) {
	ClientMode elem(client, "");
	_clients[client.getSocket()] = elem;
}

void                Channel::removeClient(Client& client) {
    _clients.erase(client.getSocket());
}

void                Channel::addInvit(Client& client) {
    _invit.push_back(&client);
}

void                Channel::removeInvit(Client& client) {
    std::vector<Client*>::iterator it = std::find(_invit.begin(), _invit.end(), &client);
    if (it != _invit.end()) {
        _invit.erase(it);
    }
}

void                Channel::broadcastMessage(Client& client, string message) {
    // TODO
    std::cout << "broadcastMessage called" << std::endl;
    (void)client;
    (void)message;
    return ;
};

void           Channel::setName(string name) {_name = name;}
void           Channel::setTopic(string topic) {_topic = topic;}
void           Channel::setMode(string mode) {_mode = mode;}
void           Channel::setPassword(string password) {_password = password;}
string         Channel::getName() const {return _name;}
string         Channel::getTopic() const {return _topic;}
string         Channel::getMode() const {return _mode;}
string         Channel::getPassword() const {return _password;}
