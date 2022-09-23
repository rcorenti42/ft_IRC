/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 02:35:12 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define ERR_NONICKNAMEGIVEN 431
#define ERR_NICKNAMEINUSE 433
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTERED 462
#define ERR_PASSWDMISMATCH 464	

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

//todo
int	TIME(Commands *command)
{
	std::cout << command->getServer()->getTime() << std::endl;
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

std::string	RPL_WELCOME(std::string nick, std::string user) {
	return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + user;
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