/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/21 00:17:30 by sobouatt         ###   ########.fr       */
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
	std::string					_message;
	std::vector<std::string>	_args;
public:
	Commands(std::string str) //constructor for testing purpose
	{
		size_t pos;
		if ((pos = str.find(":")) != std::string::npos) {
			this->_message = str.substr(pos + 1);
			str.erase(pos);
		}
		while ((pos = str.find(" ")) != std::string::npos) {
			this->_args.push_back(str.substr(0, pos));
			str.erase(0, pos + 1);
		}
		this->_args.push_back(str);
		_command = *(_args.begin());
		this->_args.erase(this->_args.begin());
		std::cout << "command : " << this->_command << std::endl;
		std::cout << "args : {";
		for (std::vector<std::string>::iterator it = this->_args.begin(); it != this->_args.end(); it++)
			std::cout << (*it) << ", ";
		std::cout << "}" << std::endl;
		std::cout << "message : " << this->_message;
	}
	Commands(Client *client, Server *server, std::string str) : _client(client), _server(server)
	{
		size_t pos;
		if ((pos = str.find(":")) != std::string::npos) {
			this->_message = str.substr(pos + 1);
			str.erase(pos);
		}
		while ((pos = str.find(" ")) != std::string::npos) {
			this->_args.push_back(str.substr(0, pos));
			str.erase(0, pos + 1);
		}
		this->_args.push_back(str);
		_command = *(_args.begin());
		this->_args.erase(this->_args.begin());
		std::cout << "command : " << this->_command << std::endl;
		std::cout << "args : {";
		for (std::vector<std::string>::iterator it = this->_args.begin(); it != this->_args.end(); it++)
			std::cout << (*it) << ", ";
		std::cout << "}" << std::endl;
		std::cout << "message : " << this->_message;
	}

	std::string					getCommand() const {
		return this->_command;
	};
	std::string					getMessage() const {
		return this->_message;
	};
	std::vector<std::string>	getArgs() const {
		return this->_args;
	};
	Client*						getClient() const {
		return this->_client;
	};
	Server*						getServer() const {
		return this->_server;
	};
};

#endif