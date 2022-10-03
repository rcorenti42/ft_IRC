/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/03 11:30:32 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Commands::Commands(std::string str) //constructor for testing purpose
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
	this->_command = *(this->_args.begin());
	for (size_t i = 0; i < this->_command.length(); i++)
		this->_command[i] = std::toupper(this->_command[i]);
	this->_args.erase(this->_args.begin());
	std::cout << "command : " << this->_command << std::endl;
	std::cout << "args : {";
	for (std::vector<std::string>::iterator it = this->_args.begin(); it != this->_args.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << "}" << std::endl;
}

Commands::Commands(Client *client, Server *server, std::string str) : _client(client), _server(server)
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
	this->_command = *(this->_args.begin());
	for (size_t i = 0; i < this->_command.length(); i++)
		this->_command[i] = toupper(this->_command[i]);
	this->_args.erase(this->_args.begin());
	std::cout << "command : " << this->_command << std::endl;
	std::cout << "args : {";
	for (std::vector<std::string>::iterator it = this->_args.begin(); it != this->_args.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << "}" << std::endl;
	std::cout << "message : " << this->_message << std::endl;
}
std::string					Commands::getCommand() const {
	return this->_command;
};
std::string					Commands::getMessage() const {
	return this->_message;
};
std::vector<std::string>	Commands::getArgs() const {
	return this->_args;
};
Client&						Commands::getClient() {
	return *this->_client;
};
Server&						Commands::getServer() {
	return *this->_server;
};
std::string					Commands::sendRep(int code, Context &context) {
	return CommandManager::getInstance()->getReply(code, context);
};

Context &Commands::getContext() {
	context.client = _client;
	return context;
}
