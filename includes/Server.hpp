/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/28 16:30:40 by lothieve         ###   ########.fr       */
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

class Server {
    std::string                     _password;
	std::string						_name;
	ConnectionManager				*_connectionManager;
    time_t							_ping;
    std::map<int, Client*>          _clients;
    std::map<std::string, Channel>  _channels;
    void                	acceptClient();
public:
	Server();
    void                	init(int port, char *password);
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
};
