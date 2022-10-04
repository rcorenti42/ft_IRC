/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/04 12:18:28 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandsRet.hpp"

std::string to_string(int n)
{
	std::ostringstream ss;
	ss << n;
	return ss.str();
};

void	PASS(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (context.client->getStats() == REGISTERED)
		context.client->writePrefixMsg(cmdmgr->getReply(462, context));
	else if (*args == Server::getInstance()->getPassword())
		context.client->setState(REGISTERED);
	else 
		context.client->writePrefixMsg(cmdmgr->getReply(464, context));
};

void	NICK(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	context.args = args;
	if (!args || args->empty())
		context.client->writePrefixMsg(cmdmgr->getReply(431, context));
	else if (Server::getInstance()->isNickTaken(*args)) 
		context.client->writePrefixMsg(cmdmgr->getReply(433, context));
	else {
		context.client->setNickname(*args);
		context.client->writePrefixMsg("NICK :" + context.client->getNickname());
	}
}

void	USER(Context &context, std::string *args) 
{
	(void) args;
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writePrefixMsg(cmdmgr->getReply(461, context));
	else if (!context.client->getRealname().empty())
		context.client->writePrefixMsg(cmdmgr->getReply(462, context));
	else {
		context.client->setUsername(*args);
		if (!context.message || context.message->empty())
			context.client->setRealName(*context.message);
	}
};

void	ISON(Context &context, std::string *args) {
	size_t pos;
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writePrefixMsg(cmdmgr->getReply(461, context));
	std::string str = *context.message;
	std::vector<Client *> clients = Server::getInstance()->getClients();
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
	context.client->writePrefixMsg(ret);
}

void	INFO(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	*context.info = std::string("");
	*context.info += " ______________________________________________ ";
	*context.info += "<                    IR-C4                     >";
	*context.info += "<                    2022                      >";
	*context.info += "< Core developpers:                            >";
	*context.info += "<     rcorenti, rcorenti@student.42.fr         >";
	*context.info += "<     lothieve, lothieve@student.42.fr         >";
	*context.info += "<     sobouatt, sobouatt@student.42.fr         >";
	*context.info += "< IR-C4 is best experienced with an IRC client >";
	*context.info += " ---------------------------------------------- ";
	*context.info += "                         \\                     ";
	*context.info += "                          \\                    ";
	*context.info += "                                       _ _      ";
	*context.info += "                            | \\__/|  .~    ~.  ";
	*context.info += "                            /oo `./      .'     ";
	*context.info += "                           {o__,   \\    {      ";
	*context.info += "                             / .  . )    \\     ";
	*context.info += "                             `-` '-' \\    }    ";
	*context.info += "                            .(   _(   )_.'      ";
	*context.info += "                           '---.~_ _ _|         ";
	context.client->writePrefixMsg(cmdmgr->getReply(371, context));
	context.client->writePrefixMsg(cmdmgr->getReply(374, context));
	(void) args;
}

void	PING(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writePrefixMsg(cmdmgr->getReply(409, context));
	else
		context.client->writePrefixMsg("PONG :" + *args);
}

void	PONG(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	std::string str;
	if (!args || args->empty())
		context.client->writePrefixMsg(cmdmgr->getReply(409, context));
	else
		context.client->setPing(std::time(NULL));
}

void	MOTD(Context &context, std::string *args) {
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
	context.client->writePrefixMsg(message);
	(void) args;
}

void  LUSERS(Context &context, std::string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();

	context.client->writePrefixMsg(cmdmgr->getReply(251, context));
	context.client->writePrefixMsg(cmdmgr->getReply(252, context));
	context.client->writePrefixMsg(cmdmgr->getReply(253, context));
	context.client->writePrefixMsg(cmdmgr->getReply(254, context));
	context.client->writeMessage(cmdmgr->getReply(255, context));
	(void)args;
}

void 	clientMode(Context &context, std::string modestring)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	std::string ret = context.client->getMode();
	std::string changes;

	int mode = 1;
	size_t pos;

	if (modestring[0] == '-') {
		mode = 0;
		modestring.erase(0, 1);
	}
	else if (modestring[0] == '+')
		modestring.erase(0, 1);
	if (modestring.find_first_not_of("isw") != std::string::npos)
		context.client->writePrefixMsg(cmdmgr->getReply(501, context));
	if (mode == 0) {
		changes += '-';
		if (modestring.find('i') != std::string::npos && (pos = ret.find('i')) != std::string::npos) {
			changes += 'i';
			ret.erase(pos, pos + 1);
		}
		if (modestring.find('s') != std::string::npos && (pos = ret.find('s')) != std::string::npos) {
			changes += 's';
			ret.erase(pos, pos + 1);
		}
	}
	else if (mode == 1) {
		changes += '+'; 
		if (modestring.find('i') != std::string::npos && (pos = ret.find('i')) == std::string::npos)
			ret += 'i';
		if (modestring.find('s') != std::string::npos && (pos = ret.find('s')) == std::string::npos)
			ret += 's';			
	}
	context.client->setMode(ret);
	// command->getClient().writePrefixMsg() a ne pas oublier
}

//opsitnmlbvk

// void	channelMode(Commands *command, std::string modestring)
// {
// 	std::string ret = command->getClient().getMode();
	
// }

void MODE(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	context.info = args;
	if ((*args)[0] == '#' || (*args)[0] == '&')
	{
		try {context.channel = &Server::getInstance()->findChannel(*args);}
		catch (Server::ChannelNotFoundException &e)
		{
			context.client->writePrefixMsg(cmdmgr->getReply(403, context));
			return ;
		}
		if (args[1].empty() || args[2].empty())
			context.client->writePrefixMsg(cmdmgr->getReply(324, context));
		// else
		// 	channelMode(command, args[1]);
	}
	else
	{
		if (args[0] != context.client->getNickname())
		{
			std::vector<Client *> clients = Server::getInstance()->getClients();
			for (std::vector<Client *>::iterator it = clients.begin(); it < clients.end(); it++)
				if ((*it)->getNickname() == args[0]) {
					context.client->writePrefixMsg(cmdmgr->getReply(502, context));
					return ;
				}
			++context.info;
			context.client->writePrefixMsg(cmdmgr->getReply(401, context));
		}
		else if (args[1].empty() || args[2].empty())
			context.client->writePrefixMsg(cmdmgr->getReply(221, context));
		else
			clientMode(context, args[1]);
	
	}
}

void JOIN(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	std::vector<std::string> names;
	std::vector<std::string> keys;
	int start = 0;
	int end;
	if (!args || args->empty())
		context.client->writePrefixMsg(cmdmgr->getReply(461, context));
	else
	{
		end = args->find(',');
		while (end != -1)
		{
			names.push_back(args->substr(start, end - start));
			start = end + 1;
			end = args->find(',', start);
		}
		names.push_back(args->substr(start));
		if (!args[1].empty())
		{
			++args;
			start = 0;
			end = args->find(',');
			while (end != -1)
			{
				keys.push_back(args->substr(start, end - start));
				start = end + 1;
				end = args->find(',', start);
			}
			keys.push_back(args->substr(start));
		}
		for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++)
		{
			if ((*it)[0] != '#' && (*it)[0] != '&')
				context.client->writePrefixMsg(*context.client, cmdmgr->getReply(476, context));
			else {
				Channel& channel = Server::getInstance()->getChannel(*it);
				context.channel = &channel;
				if (channel.getClients().empty())
					channel.addOperator(*context.client);
				channel.addClient(*context.client);
				if (!channel.getTopic().empty())
					context.client->writePrefixMsg(cmdmgr->getReply(332, context));
				channel.broadcastMessage(*context.client, "JOIN :" + channel.getName());
			}
		}
	}
};

void	PRIVMSG(Context &context, std::string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();
	int							start = 0;
	int							end;
	std::vector<std::string>	channels;
	std::vector<std::string>	clients;
	if (!args || args->empty()) {
		context.client->writePrefixMsg(cmdmgr->getReply(411, context));
		return ;
	}
	if (!context.message || context.message->empty()) {
		context.client->writePrefixMsg(cmdmgr->getReply(412, context));
		return ;
	}
	end = args->find(',');
	while (end != -1) {
		if (args->substr(start, end - start)[0] == '#' || args->substr(start, end - start)[0] == '&')
			channels.push_back(args->substr(start, end - start));
		else
			clients.push_back(args->substr(start, end - start));
		start = end + 1;
		end = args->find(',', start);
	}
	if (args->substr(start)[0] == '#' || args->substr(start)[0] == '&')
		channels.push_back(args->substr(start));
	else
		clients.push_back(args->substr(start));
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel&				chan = Server::getInstance()->getChannel(*it);
		std::vector<Client*>	cli = chan.getClients();
		for (std::vector<Client*>::iterator iter = cli.begin(); iter != cli.end(); iter++)
			if ((*iter)->getNickname() != context.client->getNickname())
				context.client->writePrefixMsg(*(*iter), "PRIVMSG " + *it + " :" + *context.message);
	}
	for (std::vector<std::string>::iterator it = clients.begin(); it != clients.end(); it++)
		context.client->writePrefixMsg(*Server::getInstance()->getClient(*it), "PRIVMSG " + *it + " :" + *context.message);
};

void	PART(Context &context, std::string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();
	int							start = 0;
	int							end;
	std::vector<std::string>	channels;
	if (!args || args->empty()) {
		context.client->writePrefixMsg(cmdmgr->getReply(403, context));
		return ;
	}
		end = args->find(',');
		while (end != -1) {
			channels.push_back(args->substr(start, end - start));
			start = end + 1;
			end = args->find(',', start);
		}
		channels.push_back(args->substr(start));
		for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++) {
			if (!Server::getInstance()->getChannel(*it).getClients().empty()) {
				if (Server::getInstance()->getChannel(*it).getClientsMap().find(context.client->getSocket()) == Server::getInstance()->getChannel(*it).getClientsMap().end())
					context.client->writePrefixMsg(cmdmgr->getReply(403, context));
				else {
					Server::getInstance()->getChannel(*it).broadcastMessage(*context.client, "PART " + *it);
					Server::getInstance()->getChannel(*it).removeClient(*context.client);
				}
			}
			else context.client->writePrefixMsg(cmdmgr->getReply(403, context));
		}
};

void	TOPIC(Context &context, std::string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();
	if (!args || args->empty()) {
		context.client->writePrefixMsg(cmdmgr->getReply(403, context));
		return ;
	}
	if (!context.message || context.message->empty()) {
		if (Server::getInstance()->getChannel(*args).getTopic().empty())
			context.client->writePrefixMsg(cmdmgr->getReply(331, context));
		else
			context.client->writePrefixMsg(cmdmgr->getReply(332, context));
	}
	else if (!Server::getInstance()->getChannel(*args).isOperator(context.client->getNickname()))
		context.client->writePrefixMsg(cmdmgr->getReply(482, context));
	else {
		Server::getInstance()->getChannel(*args).setTopic(*context.message);
		context.client->writePrefixMsg(/*command->getPacket()*/ "zbeb zbeb");
	}
};

void	OPER(Context &context, std::string *args) {
		CommandManager *cmdmgr = CommandManager::getInstance();
		context.client->writePrefixMsg(cmdmgr->getReply(491, context));
		(void) args;
};

void	QUIT(Context &context, std::string *args) {
	if (context.message && !context.message->empty())
		context.client->setQuitMessage("QUIT :" + *context.message);
	context.client->setState(NONE);
	(void) args;
};
