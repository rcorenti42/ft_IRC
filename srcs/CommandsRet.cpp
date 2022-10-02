/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/02 22:24:29 by sobouatt         ###   ########.fr       */
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
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(462));
	else if (*(command->getArgs().begin()) == command->getServer().getPassword())
		command->getClient().setState(REGISTERED);
	else
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(464));
};

void NICK(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(431));
	else
	{
		std::vector<Client *> clients = command->getServer().getClients();
		for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (*(command->getArgs().begin()) == (*it)->getNickname())
			{
				command->getClient().writePrefixMsg(command->getClient(), command->sendRep(433, command->getArgs()[0]));
				return;
			}
		}
		command->getClient().writePrefixMsg(command->getClient(), "NICK :" + *command->getArgs().begin());
		command->getClient().setNickname(*command->getArgs().begin());
	}
}

// add the other fields ?
void USER(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(461, command->getCommand()));
	else if (!command->getClient().getRealname().empty())
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(462));
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
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(461, command->getCommand()));
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
	command->getClient().writePrefixMsg(command->getClient(), ret);
}

void INFO(Commands *command)
{
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, " ______________________________________________"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "<                    IR-C4                     >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "<                    2022                      >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "< Core developpers:                            >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "<     rcorenti, rcorenti@student.42.fr         >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "<     lothieve, lothieve@student.42.fr         >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "<     sobouatt, sobouatt@student.42.fr         >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "< IR-C4 is best experienced with an IRC client >"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, " ----------------------------------------------"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                         \\"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                          \\"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                                       _ _"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                            | \\__/|  .~    ~."));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                            /oo `./      .'"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                           {o__,   \\    {"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                             / .  . )    \\"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                             `-` '-' \\    }"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                            .(   _(   )_.'"));
    command->getClient().writePrefixMsg(command->getClient(), command->sendRep(371, "                           '---.~_ _ _|"));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(374));
}

void TIME(Commands *command)
{
	// struct tm *readable = localtime(command->getServer()->getPing());
	std::string str = command->sendRep(391, "localtime");
	str += " :";
	// str += asctime(readable);
	command->getClient().writePrefixMsg(command->getClient(), str);
}

void PING(Commands *command)
{
	if (command->getArgs().empty())
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(409));
	else
		command->getClient().writePrefixMsg(command->getClient(), "PONG :" + command->getArgs()[0]);
}

void PONG(Commands *command)
{
	std::string str;
	if (command->getArgs().empty())
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(409));
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
	command->getClient().writePrefixMsg(command->getClient(), message);
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
			if ((*it)->getMode().find('i') == std::string::npos)
				visibles++;
			else
				invisibles++;
			if ((*it)->getMode().find('o') != std::string::npos)
				operators++;
		}
		else
			unknown++;
	}
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(251, to_string(visibles), to_string(invisibles)));
	if (operators)
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(252, to_string(operators)));
	if (unknown)
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(253, to_string(unknown)));
	if (channels)
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(254, to_string(channels)));
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(255, to_string(visibles + invisibles)));
}

void 	clientMode(Commands *command, std::string modestring)
{
	std::string ret = command->getClient().getMode();
	int mode = 1;
	size_t pos;

	if (modestring[0] == '-') {
		mode = 0;
		modestring.erase(0, 1);
	}
	else if (modestring[0] == '+')
		modestring.erase(0, 1);
	if (modestring.find_first_not_of("isw") != std::string::npos)
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(501, command->getClient().getNickname()));
	if (mode == 0) {
		if (modestring.find('i') != std::string::npos && (pos = ret.find('i')) != std::string::npos)
			ret.erase(pos, pos + 1);
		if (modestring.find('s') != std::string::npos && (pos = ret.find('s')) != std::string::npos)
			ret.erase(pos, pos + 1);
	}
	else if (mode == 1)
	{
		if (modestring.find('i') != std::string::npos && (pos = ret.find('i')) == std::string::npos)
			ret += 'i';
		if (modestring.find('s') != std::string::npos && (pos = ret.find('s')) == std::string::npos)
			ret += 's';			
	}
	command->getClient().setMode(ret);
}

void MODE(Commands *command)
{
	std::vector<std::string> args = command->getArgs();
	if (args.begin()[0][0] == '#' || args.begin()[0][0] == '#')
	{
	}
	else
	{
		if (args[0] != command->getClient().getNickname())
		{
			std::vector<Client *> clients = command->getServer().getClients();
			for (std::vector<Client *>::iterator it = clients.begin(); it < clients.end(); it++)
				if ((*it)->getNickname() == args[0]) {
					command->getClient().writePrefixMsg(command->getClient(), command->sendRep(502));
					return ;
				}
			command->getClient().writePrefixMsg(command->getClient(), command->sendRep(401, args[1]));
		}
		else if (args.size() < 2)
			command->getClient().writePrefixMsg(command->getClient(), command->sendRep(221, "+" + command->getClient().getMode()));
		else
			clientMode(command, args[1]);
	
	}
}

// void MODE(Commands *command)
// {
// 	std::vector<std::string> args = command->getArgs();
// 	if (args.begin()[0][0] == '#' || args.begin()[0][0] == '#')
// 	{
// 	}
// 	else
// 	{
// 		if (args[1] != command->getClient().getNickname())
// 		{
// 			std::vector<Client *> clients = command->getServer().getClients();
// 			for (std::vector<Client *>::iterator it = clients.begin(); it < clients.end(); it++)
// 				if ((*it)->getNickname() == args[1]) {
// 					command->getClient().writePrefixMsg(command->getClient(), command->sendRep(502));
// 					return ;
// 				}
// 			command->getClient().writePrefixMsg(command->getClient(), command->sendRep(401, args[1]));
// 		}
// 	}
// }

void JOIN(Commands *command)
{
	std::vector<std::string> names;
	std::vector<std::string> keys;
	int start = 0;
	int end;
	if (command->getArgs().empty())
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(461, "JOIN"));
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
				command->getClient().writePrefixMsg(command->getClient(), command->sendRep(476, *it));
			else {
				Channel& channel = command->getServer().getChannel(*it);
				if (channel.getClients().empty())
					channel.addOperator(command->getClient());
				channel.addClient(command->getClient());
				if (!channel.getTopic().empty())
					command->getClient().writePrefixMsg(command->getClient(), command->sendRep(332, *it, channel.getTopic()));
				channel.broadcastMessage(command->getClient(), "JOIN :" + channel.getName());
			}
		}
	}
};

void	PRIVMSG(Commands* command) {
	int							start = 0;
	int							end;
	std::vector<std::string>	channels;
	std::vector<std::string>	clients;
	if (!command->getArgs().empty()) {
		if (!command->getMessage().empty()) {
			end = command->getArgs()[0].find(',');
			while (end != -1) {
				if (command->getArgs()[0].substr(start, end - start)[0] == '#' || command->getArgs()[0].substr(start, end - start)[0] == '&')
					channels.push_back(command->getArgs()[0].substr(start, end - start));
				else
					clients.push_back(command->getArgs()[0].substr(start, end - start));
				start = end + 1;
				end = command->getArgs()[0].find(',', start);
			}
			if (command->getArgs()[0].substr(start)[0] == '#' || command->getArgs()[0].substr(start)[0] == '&')
				channels.push_back(command->getArgs()[0].substr(start));
			else
				clients.push_back(command->getArgs()[0].substr(start));
			for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++) {
				Channel&				chan = command->getServer().getChannel(*it);
				std::vector<Client*>	cli = chan.getClients();
				for (std::vector<Client*>::iterator iter = cli.begin(); iter != cli.end(); iter++)
					if ((*iter)->getNickname() != command->getClient().getNickname())
						command->getClient().writePrefixMsg(*(*iter), "PRIVMSG " + *it + " :" + command->getMessage());
			}
			for (std::vector<std::string>::iterator it = clients.begin(); it != clients.end(); it++)
				command->getClient().writePrefixMsg(*command->getServer().getClient(*it), "PRIVMSG " + *it + " :" + command->getMessage());
		} else
			command->getClient().writePrefixMsg(command->getClient(), command->sendRep(412));
	} else
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(411, command->getCommand()));
};

void	PART(Commands* command) {
	int							start = 0;
	int							end;
	std::vector<std::string>	channels;
	if (!command->getArgs().empty()) {
		end = command->getArgs()[0].find(',');
		while (end != -1) {
			channels.push_back(command->getArgs()[0].substr(start, end - start));
			start = end + 1;
			end = command->getArgs()[0].find(',', start);
		}
		channels.push_back(command->getArgs()[0].substr(start));
		for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++) {
			if (!command->getServer().getChannel(*it).getClients().empty()) {
				if (command->getServer().getChannel(*it).getClientsMap().find(command->getClient().getSocket()) == command->getServer().getChannel(*it).getClientsMap().end())
					command->getClient().writePrefixMsg(command->getClient(), command->sendRep(442, *it));
				else {
					command->getServer().getChannel(*it).broadcastMessage(command->getClient(), "PART " + *it);
					command->getServer().getChannel(*it).removeClient(command->getClient());
				}
			} else
				command->getClient().writePrefixMsg(command->getClient(), command->sendRep(403, *it));
		}
	} else
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(461, "PART"));
};

void	TOPIC(Commands* command) {
	if (!command->getArgs().empty()) {
		if (command->getMessage().empty())
			if (command->getServer().getChannel(command->getArgs()[0]).getTopic().empty())
				command->getClient().writePrefixMsg(command->getClient(), command->sendRep(331, command->getArgs()[0]));
			else
				command->getClient().writePrefixMsg(command->getClient(), command->sendRep(332, command->getArgs()[0], command->getServer().getChannel(command->getArgs()[0]).getTopic()));
		else
			if (!command->getServer().getChannel(command->getArgs()[0]).isOperator(command->getClient().getNickname()))
				command->getClient().writePrefixMsg(command->getClient(), command->sendRep(482, command->getArgs()[0]));
			else {
				command->getServer().getChannel(command->getArgs()[0]).setTopic(command->getMessage());
				command->getClient().writePrefixMsg(command->getClient(), command->getPacket());
			}
	} else
		command->getClient().writePrefixMsg(command->getClient(), command->sendRep(461, "TOPIC"));
};

void	OPER(Commands* command) {
	command->getClient().writePrefixMsg(command->getClient(), command->sendRep(491));
};
