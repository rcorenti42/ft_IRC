/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:22 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/14 16:48:15 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <sstream>
#include "Client.hpp"
#include "Server.hpp"
#include <cstring>
#include <vector>

using std::string;
class Channel;
class Server;
class Client;


struct Context {
	Client	*client;
	Channel	*channel;
	string	*info;
	string	*message;
	string	*args;
	string	*packet;
};

void	PASS(Context &context, string *args);
void	NICK(Context &context, string *args);
void	USER(Context &context, string *args);
void	INFO(Context &context, string *args);
void	MOTD(Context &context, string *args);
void	LUSERS(Context &context, string *args);
void	PING(Context &context, string *args);
void	PONG(Context &context, string *args);
void	MODE(Context &context, string *args);
void	ISON(Context &context, std::string *args);
void	JOIN(Context &context, string *args);
void	PRIVMSG(Context &context, string *args);
void	NOTICE(Context &context, string *args);
void	PART(Context &context, string *args);
void	TOPIC(Context &context, string *args);
void	QUIT(Context &context, string *args);
void	OPER(Context &context, string *args);
void	VERSION(Context &context, string *args);
void	KICK(Context &context, string *args);


class CommandManager {
private:
	typedef void (*t_command)(Context &, string *);
	struct Command {
		string	id;
		string	*args;
		string	message;
	};

	CommandManager();

	static CommandManager *_instance;
	std::map<string, t_command> _listCommands;
	string replies[1000];
public:
	class CommandException : std::exception {
		private:
			const string &_what;
		public:
			CommandException(const string &what);
			const char *what() const throw();
	};

	static	CommandManager *getInstance();
	string	getReply(int code, Context context);
	void	sendReply(int code, Context context);
	void	execute(string &packet, Client &client);
	void	parsePacket(const string &packet, Command *result, std::vector<string> &arg_vec);
	void    registerClient(Client &client, Context &context);
};
