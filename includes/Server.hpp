/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 03:25:04 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sstream>
# include <iostream>
# include <cctype>
# include <vector>
# include <map>
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <poll.h>
# include "Channel.hpp"

class Client;

class Server {
    int                             _sock;
    int                             _port;
    std::string                     _password;
	std::string						_name;
    time_t							_ping;
	std::vector<pollfd>             _fds;
    std::map<int, Client*>          _clients;
    std::map<std::string, Channel>  _channels;
    bool                	validPort(char* port);
    void                	acceptClient();
public:
	Server();
    void                	setPort(char* port);
    void                	setPassword(char* password);
    void                	init();
    Client*             	getClient(std::string nickName);
    std::vector<Client*>    getClients();
    Channel&                getChannel(std::string name);
    std::vector<Channel*>   getChannels();
	std::string				getPassword() const;
	std::string				getName() const;
    void                    sendPing();
    void                    erraseClient(Client client);
    void                    erraseChannel(Channel channel);
    void                    run();
};

#endif