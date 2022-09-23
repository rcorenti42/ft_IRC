/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 03:52:23 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "CommandsRet.hpp"
#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define RPL_TIME 391
#define ERR_NONICKNAMEGIVEN 431
#define ERR_NICKNAMEINUSE 433
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTERED 462
#define ERR_PASSWDMISMATCH 464	

std::string format_num_replay(Commands* command, int code)
{
	std::stringstream ss;
	ss << ":" << command->getServer()->getName() << " " << code << " " << command->getClient()->getNickname();
	return (ss.str());
}

int	PASS(Commands* command)
{
	if (command->getClient()->getStats() == REGISTERED)
		return (ERR_ALREADYREGISTERED);
	if (*(command->getArgs().begin()) == command->getServer()->getPassword())
	{
		command->getClient()->setState(CHECKPASS);	
		return (0);
	}
	else 
		return (ERR_PASSWDMISMATCH);
};

int	NICK(Commands *command)
{
	if (command->getArgs().empty())
		return (ERR_NONICKNAMEGIVEN);
	std::vector<Client *> clients = command->getServer()->getClients();
	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++	)
	{
		if (*(command->getArgs().begin()) == (*it)->getNickname())
			return (ERR_NICKNAMEINUSE);
	}
	command->getClient()->setNickname(*(command->getArgs().begin()));
	command->getClient()->setState(CONNECTED);
	return (0);
}

//add the other fields ?
int	USER(Commands *command)
{
	if (command->getArgs().empty())
		return (ERR_NEEDMOREPARAMS);
	if (command->getClient()->getStats() == REGISTERED)
		return (ERR_ALREADYREGISTERED);
	command->getClient()->setUsername(*(command->getArgs().begin()));
	if (!command->getMessage().empty())
		command->getClient()->setRealName(command->getMessage());
	return (0);	
};

int	TIME(Commands *command)
{
	struct tm *readable = localtime(command->getServer()->getTime());

	std::string str = format_num_replay(command, RPL_TIME);
	str += " :";
	str += asctime(readable);
	command->getClient()->writeMessage(str);
	return (0);
}

int PING(Commands *command)
{
	if (command->getArgs().empty())
		return (ERR_NEEDMOREPARAMS);
	else
		std::cout << "PON";
	return (0);
	
}

std::string	RPL_WELCOME(std::string nick, std::string user, std::string addr) {
	return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + addr;
};

std::string	RPL_YOURHOST() {
	return ":Your host is 42, running version 420";
};

std::string	RPL_CREATED() {
	return ":This server was created 42/42/4242";
};

std::string	RPL_MYINFO() {
	return "42 420 w n";
};