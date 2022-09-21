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

Channel::Channel() {
    // TODO
    std::cout << "Channel constructor called" << std::endl;
};
void                Channel::setName(std::string name) {
    this->_name = name;
};
void                Channel::setTopic(std::string topic) {
    this->_topic = topic;
};
void                Channel::setMode(std::string mode) {
    this->_mode = mode;
};
void                Channel::setPassword(std::string password) {
    this->_password = password;
};
void                Channel::setmodeClients(std::string modeClients, Client& client) {
    this->_modeClients[client.getSocket()] = modeClients;
};
std::string         Channel::getName() const {
    return this->_name;
};
std::string         Channel::getTopic() const {
    return this->_topic;
};
std::string         Channel::getMode() const {
    return this->_mode;
};
std::string         Channel::getPassword() const {
    return this->_password;
};
std::string         Channel::getmodeClients(Client& client) const {
    return this->_modeClients.at(client.getSocket());
};
std::vector<Client*> Channel::getClients() const {
    std::vector<Client*> clients;
    for (std::map<int, Client*>::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        clients.push_back(it->second);
    }
    return clients;
};
void                Channel::addClient(Client& client) {
    this->_clients[client.getSocket()] = &client;
};
void                Channel::removeClient(Client& client) {
    this->_clients.erase(client.getSocket());
};
void                Channel::addInvit(Client& client) {
    this->_invit.push_back(&client);
};
void                Channel::removeInvit(Client& client) {
    std::vector<Client*>::iterator it = std::find(this->_invit.begin(), this->_invit.end(), &client);
    if (it != this->_invit.end()) {
        this->_invit.erase(it);
    }
};
void                Channel::broadcastMessage(Client& client, std::string message) {
    // TODO
    std::cout << "broadcastMessage called" << std::endl;
    (void)client;
    (void)message;
    return ;
};