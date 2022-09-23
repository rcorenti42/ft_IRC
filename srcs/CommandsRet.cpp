/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 05:13:59 by sobouatt         ###   ########.fr       */
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
		command->getClient()->setState(REGISTERED);
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
	command->getClient()->writeMessage("PING :temporary ping");
	return (0);
	
}

int	PONG(Commands *command)
{
	std::string str;
	if (command->getArgs().empty())
		return (ERR_NEEDMOREPARAMS);
	str = "PONG";
	command->getClient()->writeMessage("PONG :temporary pong");
	return (0);
}

int	MOTD(Commands* command) {
	std::string	message = "";
	message += "- irc.42.org Message of the Day -\r\n";
	message += "- 2042-5-4 00:42\r\n";
	message += "- Welcome on ft_IRC Server !\r\n-\r\n-\r\n";
	message += "-          ,---.      .`````-.  \r\n";
	message += "-         /,--.|     /   ,-.  \\ \r\n";
	message += "-        //_  ||    (___/  |   |\r\n";
	message += "-       /_( )_||          .'  / \r\n";
	message += "-      /(_ o _)|      _.-'_.-'  \r\n";
	message += "-     / /(_,_)||_   _/_  .'     \r\n";
	message += "-    /  `-----' || ( ' )(__..--.\r\n";
	message += "-    `-------|||-'(_{;}_)      |\r\n";
	message += "-            '-'   (_,_)-------'\r\n-\r\n-\r\n";
	message += "- En vous connectant, vous acceptez implicitement les regles de 42school.\r\n-\r\n";
	message += "- In Trartiflette We Trust\r\n-\r\n";
	message += "- UTK SoundSystem Is Here\r\n-\r\n";
	message += "- Bonne discussion sur notre server !\r\n-\r\n";
	message += "End of /MOTD command.";
	command->getClient()->writeMessage(message);
	return 0;
}

int	LUSERS(Commands* command) {
	// TODO
	(void)command;
	return 0;
}

// int	ISON(Commands *command)
// {
	
// 	if (command->getArgs().empty())
// 		return (ERR_NEEDMOREPARAMS);
// 	std::vector<Client *> clients = command->getClients();
// 	std::vector<std::string> provided = command->getArgs();
// 	for (std::vector<std::string>::iterator it = provided.begin(); it < provided.end(); it++)
// 	{
// 		for (std::vector<Client *>)::iterator it2 = clients.begin(); it2 < clients.end(); it2++)
// 		{
// 			if (*it == (*it2))
				
// 		}
// 	}

// }

std::string	RPL_WELCOME(std::string nick, std::string user, std::string addr) {
	return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + addr;
};

std::string	RPL_YOURHOST() {
	return ":Your host is 42, running version 420";
};

std::string	RPL_CREATED() {
	return ":This server was created 4 may at 2042, 00:42:42";
};

std::string	RPL_MYINFO() {
	return "irc.42.org 420 woisx inpstmcqaovlbkSR";
};