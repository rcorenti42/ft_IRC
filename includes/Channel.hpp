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

# include <iostream>
# include <vector>
# include <map>

class Client;

class Channel {
    std::string					_name;
    std::string					_topic;
    std::string                 _mode;
    std::string                 _password;
    std::map<int, Client*>		_clients;
    std::map<int, std::string>  _modeClients;
    std::vector<Client*>		_invit;
public:
    Channel();
    void                	setName(std::string name);
    void                	setTopic(std::string topic);
    void                	setMode(std::string mode);
    void                	setPassword(std::string password);
    void                	setmodeClients(std::string modeClients, Client& client);
    std::string         	getName() const;
    std::string         	getTopic() const;
    std::string         	getMode() const;
    std::string         	getPassword() const;
    std::string         	getmodeClients(Client& client) const;
    std::vector<Client*>	getClients() const;
    void                	addClient(Client& client);
    void                	removeClient(Client& client);
    void                	addInvit(Client& client);
    void                	removeInvit(Client& client);
    void                	broadcastMessage(Client& client, std::string message);
};

#endif