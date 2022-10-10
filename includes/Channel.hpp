/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/07 06:48:17 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

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
	    Client *client;
	    string mode;
	    ClientMode(Client *c, string m) : client(c), mode(m) {}
	    ClientMode() : client(NULL), mode("") {}
    };
    string						_name;
    string						_topic;
    string                 		_mode;
    string                 		_password;
	std::map<int, Client*>		_clients;
    std::map<int, ClientMode>	_clientsWhat;
    std::vector<Client*>		_invit;
	std::vector<Client*>		_operators;
	std::vector<Client*>		_banlist;
    typedef std::map<int, ClientMode>::iterator CliIt;
    typedef std::map<int, ClientMode>::const_iterator CliCstIt;
public:
    Channel();
    Channel(string &name, Client *creator);
    void                	setName(string &name);
    void                	setTopic(string &topic);
    void                	setMode(string &mode);
    void                	setPassword(string password);
    const string		    &getName() const;
    const string		    &getTopic() const;
    const string		    &getMode() const;
    const string		    &getPassword() const;
    void                	addClient(Client *client);
	Client*					getClient(string name);
    std::vector<Client*>	getClients();
	std::vector<Client *>	getBanlist();
	std::map<int, Client*>	getClientsMap();
	string					getClientsList();
	size_t					getVisiblesNbr();
	bool					isOperator(std::string client);
	bool					isBanned(std::string client);
	bool					isClient(Client& client);
    void                	addClient(Client& client);
	void					addBanned(Client &client);
	void					addOperator(Client& client);
    void                	removeClient(Client& client);
    void                	addInvit(Client& client);
    void                	removeInvit(Client& client);
    void                	broadcastMessage(Client& client, string message);
	bool					isOn(int socket);
	bool					isEmpty() const;
};

