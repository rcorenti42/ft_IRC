/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:22 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/03 16:30:26 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include "Client.hpp"

using std::string;
class Channel;
class Server;
class Client;

struct Context {
	Client	*client;
	Channel	*channel;
	string	*info;
	string	*message;
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
