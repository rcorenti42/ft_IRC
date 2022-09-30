/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/01 01:34:31 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "CommandsRet.hpp"
#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <sstream>

std::string to_string(int n)
{
	std::ostringstream ss;
	ss << n;
	return ss.str();
};

void PASS(Commands *command)
{
	if (command->getClient().getStats() == REGISTERED)
		command->getClient().writeMessage(command->sendRep(462));
	else if (*(command->getArgs().begin()) == command->getServer().getPassword())
		command->getClient().setState(REGISTERED);
	else
		command->getClient().writeMessage(command->sendRep(464));
};

void NICK(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writeMessage(command->sendRep(431));
	else
	{
		std::vector<Client *> clients = command->getServer().getClients();
		for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (*(command->getArgs().begin()) == (*it)->getNickname())
			{
				command->getClient().writeMessage(command->sendRep(433));
				return;
			}
		}
		command->getClient().setNickname(*(command->getArgs().begin()));
		command->getClient().writeMessage("NICK :" + command->getClient().getNickname());
	}
}

// add the other fields ?
void USER(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writeMessage(command->sendRep(461, command->getCommand()));
	else if (!command->getClient().getRealname().empty())
		command->getClient().writeMessage(command->sendRep(462));
	else
	{
		command->getClient().setUsername(*(command->getArgs().begin()));
		if (!command->getMessage().empty())
			command->getClient().setRealName(command->getMessage());
	}
};

void ISON(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writeMessage(command->sendRep(461));
	size_t pos;
	std::string str = command->getMessage();
	std::vector<Client *> clients = command->getServer().getClients();
	std::vector<std::string> provided;
	std::vector<std::string> online;
	while ((pos = str.find(" ")) != std::string::npos)
	{
		provided.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}
	provided.push_back(str);
	for (std::vector<std::string>::iterator it = provided.begin(); it < provided.end(); it++)
	{
		for (std::vector<Client *>::iterator it2 = clients.begin(); it2 < clients.end(); it2++)
		{
			if ((*it) == (*it2)->getNickname())
			{
				online.push_back(*it);
				provided.erase(it);
			}
		}
	}
	std::string ret = "Users online: ";
	for (std::vector<std::string>::iterator it = online.begin(); it < online.end(); it++)
	{
		ret += (*it);
		ret += " ";
	}
	command->getClient().writeMessage(ret);
}

void INFO(Commands *command)
{
	command->getClient().writeMessage(command->sendRep(371, "            IR-C4            "));
	command->getClient().writeMessage(command->sendRep(371, "            2022             "));
	command->getClient().writeMessage(command->sendRep(371, "Core developpers:            "));
	command->getClient().writeMessage(command->sendRep(371, "    rcorenti, rcorenti@student.42.fr"));
	command->getClient().writeMessage(command->sendRep(371, "    lothieve, lothieve@student.42.fr"));
	command->getClient().writeMessage(command->sendRep(371, "    sobouatt, sobouatt@student.42.fr"));
	command->getClient().writeMessage(command->sendRep(371, "IR-C4 is best experienced with an IRC client"));
	command->getClient().writeMessage(command->sendRep(374));
}

void TIME(Commands *command)
{
	// struct tm *readable = localtime(command->getServer()->getPing());
	std::string str = command->sendRep(391, "localtime");
	str += " :";
	// str += asctime(readable);
	command->getClient().writeMessage(str);
}

void PING(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writeMessage(command->sendRep(409));
	else
		command->getClient().writeMessage("PONG :" + command->getArgs()[0]);
}

void PONG(Commands *command)
{
	std::string str;
	if (command->getArgs().empty())
		command->getClient().writeMessage(command->sendRep(409));
	else
		command->getClient().setPing(std::time(NULL));
}

void MOTD(Commands *command)
{
	std::string message = "- IR-C4 Message of the Day -\r\n";
	message += "- 2042-5-4 00:42\r\n";
	message += "- Welcome on IR-C4 Server !\r\n-\r\n-\r\n";
	message += "-       ,---,,-.----.\r\n";
	message += "-    ,`--.' |\\    /  \\\r\n";
	message += "-    |   :  :;   :    \\\r\n";
	message += "-    :   |  '|   | .\\ :\r\n";
	message += "-    |   :  |.   : |: |\r\n";
	message += "-    '   '  ;|   |  \\ :\r\n";
	message += "-    |   |  ||   : .  /\r\n";
	message += "-    '   :  ;;   | |  \\\r\n";
	message += "-    |   |  '|   | ;\\  \\\r\n";
	message += "-    '   :  |:   ' | \\.'\r\n";
	message += "-    ;   |.' :   : :-'\r\n";
	message += "-    '---'   |   |.'\r\n";
	message += "-            `---'\r\n";
	message += "-        ,---,.   ,---,.\r\n";
	message += "-      ,'  .' | ,'  .' |\r\n";
	message += "-    ,---.'   ,---.'   ,\r\n";
	message += "-    |   |    |   |    |\r\n";
	message += "-    :   :  .':   :  .'\r\n";
	message += "-    :   |.'  :   |.'\r\n";
	message += "-    `---'    `---'     ,--,\r\n";
	message += "-      ,----..        ,--.'|\r\n";
	message += "-     /   /   \\    ,--,  | :\r\n";
	message += "-    |   :     :,---.'|  : '\r\n";
	message += "-    .   |  ;. /;   : |  | ;\r\n";
	message += "-    .   ; /--` |   | : _' |\r\n";
	message += "-    ;   | ;    :   : |.'  |\r\n";
	message += "-    |   : |    |   ' '  ; :\r\n";
	message += "-    .   | '___ \\   \\  .'. |\r\n";
	message += "-    '   ; : .'| `---`:  | '\r\n";
	message += "-    '   | '/  :      '  ; |\r\n";
	message += "-    |   :    /       |  : ;\r\n";
	message += "-     \\   \\ .'        '  ,/\r\n";
	message += "-      `---`          '--'\r\n-\r\n-\r\n";
	message += "- En vous connectant, vous acceptez implicitement les regles de 42Network.\r\n-\r\n";
	message += "- In Trartiflette We Trust\r\n-\r\n";
	message += "- UTK SoundSystem Is Here\r\n-\r\n";
	message += "- Bonne discussion sur notre server !\r\n-\r\n";
	message += "End of /MOTD command.";
	command->getClient().writeMessage(message);
}

void LUSERS(Commands *command)
{
	int visibles = 0;
	int invisibles = 0;
	int operators = 0;
	int unknown = 0;
	int channels = command->getServer().getChannels().size();
	std::vector<Client *> clients = command->getServer().getClients();
	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if ((*it)->getStats() == CONNECTED)
		{
			if ((*it)->getUsermode().find('i') == std::string::npos)
				visibles++;
			else
				invisibles++;
			if ((*it)->getUsermode().find('o') != std::string::npos)
				operators++;
		}
		else
			unknown++;
	}
	command->getClient().writeMessage(command->sendRep(251, to_string(visibles), to_string(invisibles)));
	if (operators)
		command->getClient().writeMessage(command->sendRep(252, to_string(operators)));
	if (unknown)
		command->getClient().writeMessage(command->sendRep(253, to_string(unknown)));
	if (channels)
		command->getClient().writeMessage(command->sendRep(254, to_string(channels)));
	command->getClient().writeMessage(command->sendRep(255, to_string(visibles + invisibles)));
}

void MODE(Commands *command)
{
	std::vector<std::string> args = command->getArgs();
	if (args.begin()[0][0] == '#' || args.begin()[0][0] == '#')
	{
	}
	else
	{
		if (args[1] != command->getClient().getNickname())
		{
			std::vector<Client *> clients = command->getServer().getClients();
			for (std::vector<Client *>::iterator it = clients.begin(); it < clients.end(); it++)
				if ((*it)->getNickname() == args[1]) {
					command->getClient().writeMessage(command->sendRep(502));
					return ;
				}
			command->getClient().writeMessage(command->sendRep(401, args[1]));
		}
	}
}

void JOIN(Commands *command)
{
	std::vector<std::string> names;
	std::vector<std::string> keys;
	int start = 0;
	int end;
	if (command->getArgs().empty())
		command->getClient().writeMessage(command->sendRep(461, "JOIN"));
	else
	{
		end = command->getArgs()[0].find(',');
		while (end != -1)
		{
			names.push_back(command->getArgs()[0].substr(start, end - start));
			start = end + 1;
			end = command->getArgs()[0].find(',', start);
		}
		names.push_back(command->getArgs()[0].substr(start));
		if (command->getArgs().size() > 1)
		{
			start = 0;
			end = command->getArgs()[1].find(',');
			while (end != -1)
			{
				keys.push_back(command->getArgs()[1].substr(start, end - start));
				start = end + 1;
				end = command->getArgs()[1].find(',', start);
			}
			keys.push_back(command->getArgs()[1].substr(start));
		}
		for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++)
		{
			if ((*it)[0] != '#' && (*it)[0] != '&')
				command->getClient().writeMessage(command->sendRep(476, *it));
			else
			{
				Channel &channel = command->getServer().getChannel(*it);
				if (channel.getClients().empty())
				{
					channel.addClient(command->getClient());
					channel.addOperator(command->getClient());
				}
				else
					channel.addClient(command->getClient());
				if (channel.getTopic().empty())
				{
					command->getClient().writeMessage(command->sendRep(331, *it));
				}
				else
					command->getClient().writeMessage(command->sendRep(332, *it, channel.getTopic()));
				channel.broadcastMessage(command->getClient(), "JOIN :" + *it);
			}
		}
	}
}