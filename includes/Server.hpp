/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/04 12:08:54 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <poll.h>
#include "Channel.hpp"
#include "Client.hpp"
#include "ConnectionManager.hpp"

class Client;
class Channel;

class Server {
	static Server					*_instance;
    std::string                     _password;
	std::string						_name;
	ConnectionManager				*_connectionManager;
    time_t							_ping;
    std::map<int, Client*>          _clients;
    std::map<std::string, Channel>  _channels;
    void                	acceptClient();
	Server();
public:
	typedef std::map<int, Client *>::iterator ClientIt;
	typedef std::map<int, Client *>::const_iterator ConstClientIt;
	typedef std::map<std::string, Channel>::iterator ChanIt;
	typedef std::map<std::string, Channel>::const_iterator ConstChanIt;

	class ChannelNotFoundException : std::exception {
		const char *what() const throw() {return NULL;}
	};

	class ClientNotFoundException : std::exception {
		const char *what() const throw() {return NULL;}
	};

	static Server			*getInstance();
    void           	init(int port, char *password);
    void                	setPassword(char* password);
    Client*             	getClient(std::string nickName);
    std::vector<Client*>    getClients();
    Channel&                getChannel(std::string name);
    std::vector<Channel*>   getChannels();
	std::string				getPassword() const;
	std::string				getName() const;
    void                    sendPing();
    void                    erraseClient(Client& client);
    void                    erraseChannel(Channel channel);
	void					display();
    void                    run();
	bool					isNickTaken(std::string nick);
	size_t					getUsrNbr() const;
	size_t					getInvisNbr() const;
	size_t					getVisibleNbr() const;
	size_t					getChanNbr() const;
	size_t					getOPNbr() const;
	size_t					getUnknbr() const;
	Channel					&findChannel(std::string name);
	Client					&findClient(std::string name);
};
