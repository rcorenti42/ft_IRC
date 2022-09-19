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
	std::string					_base;
	std::string					_command;
	std::string					_message;
	std::vector<std::string>	_args;
public:
	Commands(Client *client, Server *server, std::string message): _client(client), _server(server), _message(message) {
		// TODO: parse message
		std::cout << "Commands constructor called" << std::endl;
	};
	std::string					getCommand() const {
		return this->_command;
	};
	std::string					getMessage() const {
		return this->_message;
	};
	std::vector<std::string>	getArgs() const {
		return this->_args;
	};
	std::string					getBase() const {
		return this->_base;
	};
	Client*						getClient() const {
		return this->_client;
	};
	Server*						getServer() const {
		return this->_server;
	};
};

#endif