/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/03 16:40:16 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandsRet.hpp"

std::string	to_string(int n) {
	std::ostringstream	ss;
	ss << n;
	return ss.str();
};

void	PASS(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (context.client->getStats() == REGISTERED)
		context.client->writeMessage(cmdmgr->getReply(462, context));
	else if (*args == Server::getInstance()->getPassword())
		context.client->setState(REGISTERED);
	else 
		context.client->writeMessage(cmdmgr->getReply(464, context));
};

void	NICK(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writeMessage(cmdmgr->getReply(431, context));
	else if (Server::getInstance()->isNickTaken(*args)) 
		context.client->writeMessage(cmdmgr->getReply(433, context));
	else {
		context.client->setNickname(*args);
		context.client->writeMessage("NICK :" + context.client->getNickname());
	}
}

void	USER(Context &context, std::string *args) 
{
	(void) args;
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writeMessage(cmdmgr->getReply(461, context));
	else if (!context.client->getRealname().empty())
		context.client->writeMessage(cmdmgr->getReply(462, context));
	else {
		context.client->setUsername(*args);
		if (!context.message && context.message->empty())
			context.client->setRealName(*context.message);
	}
};

void	ISON(Context &context, std::string *args) {
	size_t pos;
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writeMessage(cmdmgr->getReply(461, context));
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
			if ((*it) == (*it2)->getNickname()) {
				online.push_back(*it);
				provided.erase(it);
			}
		}
	}
	std::string ret;
	ret = "Users online: ";
	for (std::vector<std::string>::iterator it = online.begin(); it < online.end(); it++)
	{
			ret += (*it);
			ret += " ";
	}
	std::cout << "isonret == " << ret << std::endl;
	// if (ret != "Users online: ")
		// ret.erase(ret.size() - 1, ret.size());
	context.client->writeMessage(ret);
}

void	INFO(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	*context.info = std::string("");
	*context.info +=	"            IRCSERV                 \n";
	*context.info +=	"             2022                   \n";
	*context.info +=	"Core developpers:                   \n";
	*context.info +=	"    rcorenti, rcorenti@student.42.fr\n";
	*context.info +=	"    lothieve, lothieve@student.42.fr\n";
	*context.info +=	"    sobouatt, sobouatt@student.42.fr\n";
	*context.info +=	"IRCSERV local time:                 \n";
	*context.info +=	"IRCSERV is best experienced with an IRC client";


	/*
	context.client->writeMessage(cmdmgr->getReply(371, "            IRCSERV          ", context));
	context.client->writeMessage(cmdmgr->getReply(371, "            2022             ", context));
	context.client->writeMessage(cmdmgr->getReply(371, "Core developpers:            ", context));
	context.client->writeMessage(cmdmgr->getReply(371, "    rcorenti, rcorenti@student.42.fr", context));
	context.client->writeMessage(cmdmgr->getReply(371, "    lothieve, lothieve@student.42.fr", context));
	context.client->writeMessage(cmdmgr->getReply(371, "    sobouatt, sobouatt@student.42.fr", context));
	context.client->writeMessage(cmdmgr->getReply(371, "IRCSERV local time: ", context));
	context.client->writeMessage(cmdmgr->getReply(371, "IRCSERV is best experienced with an IRC client", context));
	*/
	context.client->writeMessage(cmdmgr->getReply(371, context));
	context.client->writeMessage(cmdmgr->getReply(374, context));
	(void) args;
}

void	TIME(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	//struct tm *readable = localtime(command->getServer()->getPing());
	std::string str = cmdmgr->getReply(391, context);
	str += " :";
	//str += asctime(readable);
	context.client->writeMessage(str);
	(void) args;
}



void	PING(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		context.client->writeMessage(cmdmgr->getReply(409, context));
	else
		context.client->writeMessage("PONG :" + *args);
}

void	PONG(Context &context, std::string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	std::string str;
	if (!args || args->empty())
		context.client->writeMessage(cmdmgr->getReply(409, context));
	else
		context.client->setPing(std::time(NULL));
}

void	MOTD(Context &context, std::string *args) {
	std::string	message = "- irc.UTK.org Message of the Day -\r\n";
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
	message += "- En vous connectant, vous acceptez implicitement les regles de 42Network.\r\n-\r\n";
	message += "- In Trartiflette We Trust\r\n-\r\n";
	message += "- UTK SoundSystem Is Here\r\n-\r\n";
	message += "- Bonne discussion sur notre server !\r\n-\r\n";
	message += "End of /MOTD command.";
	context.client->writeMessage(message);
	(void) args;
}

void  LUSERS(Context &context, std::string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();

	int						visibles = 0;
	int						invisibles = 0;
	int						operators = 0;
	int						unknown = 0;
	int						channels = Server::getInstance()->getChannels().size();
	std::vector<Client*>	clients = Server::getInstance()->getClients();
	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
		if ((*it)->getStats() == CONNECTED) {
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
	context.client->writeMessage(cmdmgr->getReply(251, context));
	if (operators)
		context.client->writeMessage(cmdmgr->getReply(252, context));
	if (unknown)
		context.client->writeMessage(cmdmgr->getReply(253, context));
	if (channels)
		context.client->writeMessage(cmdmgr->getReply(254, context));
	context.client->writeMessage(cmdmgr->getReply(255, context));
	(void)args;
}

void	MODE(Context &context, std::string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();
	// TODO
	context.client->writeMessage(cmdmgr->getReply(221, context));
	(void) args;
}

void	JOIN(Context &context, std::string *args) {
	(void) context;
	(void) args;
}
