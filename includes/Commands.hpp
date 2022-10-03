/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/27 19:55:14 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <cctype>
# include <vector>

class Client;
class Server;

class Commands {
	Client*						_client;
	Server*						_server;
	std::string					_packet;
	std::string					_command;
	std::string					_message;
	std::vector<std::string>	_args;
public:
	Commands(std::string str); //constructor for testing purpose
	Commands(Client *client, Server *server, std::string str);
	std::string					getCommand() const;
	std::string					getMessage() const;
	std::string					getPacket() const;
	std::vector<std::string>	getArgs() const;
	Client&						getClient();
	Server&						getServer();
	std::string					sendRep(int, std::string = "", std::string = "", std::string = "");
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

#endif