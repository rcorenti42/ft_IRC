/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/18 21:19:17 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Client.hpp"
# include "Server.hpp"
# include <iostream>

class Client;
class Server;

class Commands {
	Client*						_client;
	Server*						_server;
	std::string					_command;
	std::vector<std::string>	_args;
public:
	Commands(Client *client, Server *server, std::string arg): _client(client), _server(server) {
		(void)_client;
		(void)arg;
		(void)_server;
	};
	std::string					getCommand() const {
		return this->_command;
	};
};

#endif