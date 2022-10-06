/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/04 15:07:05 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <cctype>
# include <vector>
#include "CommandManager.hpp"
#include "Client.hpp"
#include "Server.hpp"

class Client;
class Server;

class Commands {
	Client*						_client;
	Server*						_server;
	std::string					_packet;
	std::string					_command;
	std::string					_message;
	std::vector<std::string>	_args;
	Context						context;
public:
	Commands(std::string str); //constructor for testing purpose
	Commands(Client *client, Server *server, std::string str);
	std::string					getCommand() const;
	std::string					getMessage() const;
	std::string					getPacket() const;
	std::vector<std::string>	&getArgs();
	Client&						getClient();
	Server&						getServer();
	//std::string					sendRep(int, Context &);
	Context						&getContext();
};