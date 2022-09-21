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