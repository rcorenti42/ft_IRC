/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/19 23:47:55               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   Channels.hpp                                                             */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
# define CHANNELS_HPP

# include "Client.hpp"
# include <iostream>
# include <vector>
# include <map>

class Channel {
    std::string					_name;
    std::string					_topic;
    std::string                 _mode;
    std::string                 _password;
    std::map<int, Client*>		_clients;
    std::map<int, std::string>  _modeClients;
    std::vector<Client*>		_invit;
public:
    Channel() {
        // TODO
        std::cout << "Channel constructor called" << std::endl;
    };
    void                setName(std::string name) {
        this->_name = name;
    };
    void                setTopic(std::string topic) {
        this->_topic = topic;
    };
    void                setMode(std::string mode) {
        this->_mode = mode;
    };
    void                setPassword(std::string password) {
        this->_password = password;
    };
    void                setmodeClients(std::string modeClients, Client& client) {
        this->_modeClients[client.getSocket()] = modeClients;
    };
    std::string         getName() const {
        return this->_name;
    };
    std::string         getTopic() const {
        return this->_topic;
    };
    std::string         getMode() const {
        return this->_mode;
    };
    std::string         getPassword() const {
        return this->_password;
    };
    std::string         getmodeClients(Client& client) const {
        return this->_modeClients.at(client.getSocket());
    };
    std::vector<Client*> getClients() const {
        std::vector<Client*> clients;
        for (std::map<int, Client*>::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
            clients.push_back(it->second);
        }
        return clients;
    };
    void                addClient(Client& client) {
        this->_clients[client.getSocket()] = &client;
    };
    void                removeClient(Client& client) {
        this->_clients.erase(client.getSocket());
    };
    void                addInvit(Client& client) {
        this->_invit.push_back(&client);
    };
    void                removeInvit(Client& client) {
        std::vector<Client*>::iterator it = std::find(this->_invit.begin(), this->_invit.end(), &client);
        if (it != this->_invit.end()) {
            this->_invit.erase(it);
        }
    };
    void                broadcastMessage(Client& client, std::string message) {
        // TODO
        std::cout << "broadcastMessage called" << std::endl;
        (void)client;
        (void)message;
        return ;
    };
};


#endif