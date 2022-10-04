/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/03 17:36:55 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <cctype>
# include <vector>
#include "CommandManager.hpp"
#include "CommandsRet.hpp"
#include "CommandsReply.hpp"
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
	std::vector<std::string>	getArgs() const;
	Client&						getClient();
	Server&						getServer();
	//std::string					sendRep(int, Context &);
	Context						&getContext();
};

void	PASS(Commands*);
void	NICK(Commands*);
void	USER(Commands*);
void	INFO(Commands *);
void	TIME(Commands*);
void	MOTD(Commands*);
void	LUSERS(Commands*);
void	PING(Commands*);
void	PONG(Commands*);
void	MODE(Commands*);
void	ISON(Commands *);
void	JOIN(Commands*);
void	PRIVMSG(Commands*);
void	PART(Commands*);
void	TOPIC(Commands*);
void	OPER(Commands*);
void	QUIT(Commands*);
