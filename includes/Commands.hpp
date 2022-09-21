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

# include <iostream>
# include <vector>

class Client;
class Server;

class Commands {
	Client*						_client;
	Server*						_server;
	std::string					_command;
	std::string					_message;
	std::vector<std::string>	_args;
public:
	Commands(std::string str); //constructor for testing purpose
	Commands(Client *client, Server *server, std::string str);
	std::string					getCommand() const;
	std::string					getMessage() const;
	std::vector<std::string>	getArgs() const;
	Client*						getClient() const;
	Server*						getServer() const;
	void						send(int code);
};

#endif