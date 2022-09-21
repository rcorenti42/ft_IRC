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
# include "Client.hpp"
using std::string;
using std::cout;

class Client;

class Channel {
private:	
    struct ClientMode {
	    Client client;
	    string mode;
	    ClientMode(const Client &c, string m) : client(c), mode(m) {}
	    ClientMode() : client(0), mode("") {}
    };
    string					_name;
    string					_topic;
    string                 _mode;
    string                 _password;
    std::map<int, ClientMode>		_clients;
    std::vector<Client*>		_invit;
    typedef std::map<int, ClientMode>::iterator CliIt;
    typedef std::map<int, ClientMode>::const_iterator CliCstIt;
public:
    Channel();
    Channel(string &name, Client &creator);
    void                	setName(string name);
    void                	setTopic(string topic);
    void                	setMode(string mode);
    void                	setPassword(string password);
    string     		    	getName() const;
    string     		    	getTopic() const;
    string     		    	getMode() const;
    string     		    	getPassword() const;
    std::vector<Client>		getClients() const;
    void                	addClient(Client& client);
    void                	removeClient(Client& client);
    void                	addInvit(Client& client);
    void                	removeInvit(Client& client);
    void                	broadcastMessage(Client& client, string message);
};

#endif
