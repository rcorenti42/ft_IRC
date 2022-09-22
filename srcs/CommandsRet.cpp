/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/21 08:19:27 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandsRet.hpp"
#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define ERR_ALREADYREGISTERED 462
#define ERR_PASSWDMISMATCH 464

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

//////////////////////////////////////////////////////////

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