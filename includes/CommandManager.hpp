/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:22 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/04 11:19:50 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include "Client.hpp"
#include <sstream>
#include "Server.hpp"

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
	string	nbnoinvisibles;
	string	nbinvisibles;
	string	nbuoperators;
	string	nbunknown;
	string	nbchannels;
	string	nbclients;
	string	channelname;
	string	channelmode;
	string	topic;
	string	ch;
};

class CommandManager {
private:
	static CommandManager *_instance;
	string replies[1000];

	CommandManager();
public:

	static CommandManager *getInstance();
	string getReply(int code, Context context);
};
