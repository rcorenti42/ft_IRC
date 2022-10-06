/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/06 23:49:08 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

string to_string(int n)
{
	std::ostringstream ss;
	ss << n;
	return ss.str();
};

void	PASS(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (context.client->getStats() == REGISTERED)
		cmdmgr->sendReply(462, context);
	else if (*args == Server::getInstance()->getPassword())
		context.client->setState(REGISTERED);
	else 
		cmdmgr->sendReply(464, context);
};

void	NICK(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	context.args = args;
	if (!args || args->empty())
		cmdmgr->sendReply(431, context);
	else if (Server::getInstance()->isNickTaken(*args)) 
		cmdmgr->sendReply(433, context);
	else {
		context.client->writePrefixMsg("NICK :" + *args);
		context.client->setNickname(*args);
	}
}

void	USER(Context &context, string *args) 
{
	(void) args;
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		cmdmgr->sendReply(461, context);
	else if (!context.client->getRealname().empty())
		cmdmgr->sendReply(462, context);
	else {
		context.client->setUsername(*args);
		if (!context.message || context.message->empty())
			context.client->setRealName(*context.message);
	}
};

void	ISON(Context &context, string *args) {
	size_t pos;
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (!args || args->empty())
		cmdmgr->sendReply(461, context);
	string str = *context.message;
	string rep = "Users online:";
	do
	{
		pos = str.find(" ");
		try {
			Client &cl = Server::getInstance()->findClient(str.substr(0, pos));
			rep += " ";
			rep += cl.getNickname();
		}
		catch (Server::ClientNotFoundException &e) {}
		str.erase(0, pos + 1);
	}
	while (pos != string::npos);
	context.client->writePrefixMsg(rep);
}

void	INFO(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	context.info = new string("");
	*context.info += " ______________________________________________ \r\n";
	*context.info += "<                    IR-C4                     >\r\n";
	*context.info += "<                    2022                      >\r\n";
	*context.info += "< Core developpers:                            >\r\n";
	*context.info += "<     rcorenti, rcorenti@student.42.fr         >\r\n";
	*context.info += "<     lothieve, lothieve@student.42.fr         >\r\n";
	*context.info += "<     sobouatt, sobouatt@student.42.fr         >\r\n";
	*context.info += "< IR-C4 is best experienced with an IRC client >\r\n";
	*context.info += " ---------------------------------------------- \r\n";
	*context.info += "                         \\                     \r\n";
	*context.info += "                          \\                    \r\n";
	*context.info += "                                       _ _      \r\n";
	*context.info += "                            | \\__/|  .~    ~.  \r\n";
	*context.info += "                            /oo `./      .'     \r\n";
	*context.info += "                           {o__,   \\    {      \r\n";
	*context.info += "                             / .  . )    \\     \r\n";
	*context.info += "                             `-` '-' \\    }    \r\n";
	*context.info += "                            .(   _(   )_.'      \r\n";
	*context.info += "                           '---.~_ _ _|         \r\n";
	cmdmgr->sendReply(371, context);
	cmdmgr->sendReply(374, context);
	delete context.info;
	(void) args;
}

void	PING(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	if (args->empty())
		cmdmgr->sendReply(409, context);
	else
		context.client->writePrefixMsg("PONG :" + *args);
}

void	PONG(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();

	string str;
	if (args->empty())
		cmdmgr->sendReply(409, context);
	else
		context.client->setPing(std::time(NULL));
}

void	MOTD(Context &context, string *args) {
	string	message = " - IR-C4 Message of the Day -\r\n";
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

void  LUSERS(Context &context, string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();

	cmdmgr->sendReply(251, context);
	cmdmgr->sendReply(252, context);
	cmdmgr->sendReply(253, context);
	cmdmgr->sendReply(254, context);
	cmdmgr->sendReply(255, context);
	(void)args;
}

void 	clientMode(Context &context, string modestring)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	std::string ret = context.client->getMode();

	int mode = 1;
	size_t pos;

	if (modestring[0] == '-') {
		mode = 0;
		modestring.erase(0, 1);
	}
	else if (modestring[0] == '+')
		modestring.erase(0, 1);
	if (modestring.find_first_not_of("isw") != string::npos)
		cmdmgr->sendReply(501, context);
	if (mode == 0) 
	{
		if (modestring.find('i') != string::npos && (pos = ret.find('i')) != string::npos) {
			ret.erase(pos, pos + 1);
		}
		if (modestring.find('s') != string::npos && (pos = ret.find('s')) != string::npos) {
			ret.erase(pos, pos + 1);
		}
	}
	else if (mode == 1) {
		if (modestring.find('i') != string::npos && (pos = ret.find('i')) == string::npos)
			ret += 'i';
		if (modestring.find('s') != string::npos && (pos = ret.find('s')) == string::npos)
			ret += 's';			
	}
	context.client->setMode(ret);
	cmdmgr->sendReply(221, context);
}

void	channelMode(Context &context, std::string modestring)
{
	std::string ret = context.channel->getMode();
	std::cout << "ret= " << ret << std::endl;
	CommandManager *cmdmgr = CommandManager::getInstance();
	std::string flgs = "opsitnmlbv";
	size_t pos;
	int mode = 1;
	
	if (modestring[0] == '-') {
		mode = 0;
		modestring.erase(0, 1);
	}
	else if (modestring[0] == '+')
		modestring.erase(0, 1);
	if (modestring.find_first_not_of(flgs) != std::string::npos)
		cmdmgr->sendReply(501, context);
	if (mode == 0)
	{
		for (size_t i = 0; i < flgs.size(); i++)
		{
			if (modestring.find(flgs[i]) != std::string::npos && (pos = ret.find(flgs[i]) != std::string::npos))
				ret.erase(pos, pos + 1);
		}
	}
	else if (mode == 1)
	{
		for (size_t i = 0; i < flgs.size(); i++)
			if (modestring.find(flgs[i]) != std::string::npos && ret.find(flgs[i]) == std::string::npos)
				ret += flgs[i];
	}
	context.channel->setMode(ret);
	cmdmgr->sendReply(324, context);
}

void MODE(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	context.info = args;
	if ((*args)[0] == '#' || (*args)[0] == '&')
	{
		try {context.channel = &Server::getInstance()->findChannel(*args);}
		catch (Server::ChannelNotFoundException &e)
		{
			cmdmgr->sendReply(403, context);
			return ;
		}
		if (args[1].empty() || args[2].empty())
			cmdmgr->sendReply(324, context);
		else
			channelMode(context, args[1]);
	}
	else
	{
		if (args[0] != context.client->getNickname())
		{
			try {
				Server::getInstance()->findClient(*args);
				cmdmgr->sendReply(502, context);
			}
			catch (Server::ClientNotFoundException &e) {
				cmdmgr->sendReply(401, context);
			}
		}
		else if (args[1].empty() || args[2].empty())
			cmdmgr->sendReply(221, context);
		else
			clientMode(context, args[1]);
	}
}

void JOIN(Context &context, string *args)
{
	CommandManager *cmdmgr = CommandManager::getInstance();
	std::vector<string> names;
	std::vector<string> keys;
	int start = 0;
	int end;
	if (!args || args->empty())
	{
		cmdmgr->sendReply(461, context);
		return ;
	}
	end = args->find(',');
	while (end != -1)
	{
		names.push_back(args->substr(start, end - start));
		start = end + 1;
		end = args->find(',', start);
	}
	names.push_back(args->substr(start));
	std::cout << *args << std::endl;
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
	for (std::vector<string>::iterator it = names.begin(); it != names.end(); it++)
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
				cmdmgr->sendReply(332, context);
			channel.broadcastMessage(*context.client, "JOIN :" + channel.getName());
			cmdmgr->sendReply(353, context);
			cmdmgr->sendReply(366, context);
		}
	}
};

void	PRIVMSG(Context &context, string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();
	int							start = 0;
	int							end;
	std::vector<string>	channels;
	std::vector<string>	clients;
	if (!args || args->empty()) {
		cmdmgr->sendReply(411, context);
		return ;
	}
	if (!context.message || context.message->empty()) {
		cmdmgr->sendReply(412, context);
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
	for (std::vector<string>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel&				chan = Server::getInstance()->getChannel(*it);
		std::vector<Client*>	cli = chan.getClients();
		for (std::vector<Client*>::iterator iter = cli.begin(); iter != cli.end(); iter++)
			if ((*iter)->getNickname() != context.client->getNickname())
				context.client->writePrefixMsg(*(*iter), "PRIVMSG " + *it + " :" + *context.message);
	}
	for (std::vector<string>::iterator it = clients.begin(); it != clients.end(); it++)
		context.client->writePrefixMsg(*Server::getInstance()->getClient(*it), "PRIVMSG " + *it + " :" + *context.message);
};

//copier coller de la fonction PRIVMSG sans les reply.
void	NOTICE(Context& context, string* args) {
	int							start = 0;
	int							end;
	std::vector<string>	channels;
	std::vector<string>	clients;
	if (!args || args->empty() || !context.message || context.message->empty())
		return ;
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
	for (std::vector<string>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel&				chan = Server::getInstance()->getChannel(*it);
		std::vector<Client*>	cli = chan.getClients();
		for (std::vector<Client*>::iterator iter = cli.begin(); iter != cli.end(); iter++)
			if ((*iter)->getNickname() != context.client->getNickname())
				context.client->writePrefixMsg(*(*iter), "PRIVMSG " + *it + " :" + *context.message);
	}
	for (std::vector<string>::iterator it = clients.begin(); it != clients.end(); it++)
		context.client->writePrefixMsg(*Server::getInstance()->getClient(*it), "PRIVMSG " + *it + " :" + *context.message);
};

void	PART(Context &context, string *args) {
	CommandManager	*cmdmgr = CommandManager::getInstance();
	size_t			start = 0;
	size_t			end;
	std::vector<string>	channels;
	if (!args || args->empty()) {
		cmdmgr->sendReply(461, context);
		return ;
	}
	do {
		end = args->find(',', start);
		const string &name = args->substr(start, end);
		Channel &chan = Server::getInstance()->getChannel(name);

		if (chan.isEmpty()) cmdmgr->sendReply(403, context);
		else if (!chan.isOn(context.client->getSocket())) cmdmgr->sendReply(442, context);
		else {
			chan.broadcastMessage(*context.client, "PART " + name);
			chan.removeClient(*context.client);
		}
		start = end + 1;
	} while (end != string::npos);
};

void	TOPIC(Context &context, string *args) {
	CommandManager *cmdmgr = CommandManager::getInstance();
	if (!args || args->empty()) {
		cmdmgr->sendReply(461, context);
		return ;
	}
	if (!context.message || context.message->empty()) {
		if (Server::getInstance()->getChannel(*args).getTopic().empty())
			cmdmgr->sendReply(331, context);
		else
			cmdmgr->sendReply(332, context);
		return ;
	}
	if (!Server::getInstance()->getChannel(*args).isOperator(context.client->getNickname()))
		cmdmgr->sendReply(482, context);
	else {
		Server::getInstance()->getChannel(*args).setTopic(*context.message);
		context.client->writePrefixMsg(*context.packet);
	}
};

void	OPER(Context &context, string *args) {
		CommandManager *cmdmgr = CommandManager::getInstance();
		cmdmgr->sendReply(491, context);
		(void) args;
};

void	QUIT(Context &context, string *args) {
	if (context.message && !context.message->empty())
		context.client->setQuitMessage("QUIT :" + *context.message);
	context.client->setState(NONE);
	(void) args;
};

void	VERSION(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	cmdmgr->sendReply(351, context);
	(void) args;
};

void	KICK(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	if (!args || args->empty()) {
		cmdmgr->sendReply(461, context);
		return;
	}
	try {
		context.channel = &Server::getInstance()->findChannel(*args);
	}
	catch (Server::ChannelNotFoundException& e) {
		cmdmgr->sendReply(403, context);
		return ;
	}
	if (context.channel->getClientsMap().find(context.client->getSocket()) == context.channel->getClientsMap().end()) {
		cmdmgr->sendReply(442, context);
		return;
	}
	if (context.channel->isOperator(context.client->getNickname())) {
		if (context.channel->getClient(args[1])) {
			context.channel->broadcastMessage(*context.client, *context.packet);
			context.channel->removeClient(*context.channel->getClient(args[1]));
		}
	}
	else
		cmdmgr->sendReply(482, context);
};

void	NAMES(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	cmdmgr->sendReply(353, context);
	cmdmgr->sendReply(366, context);
	(void)args;
};

void	ADMIN(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	cmdmgr->sendReply(256, context);
	cmdmgr->sendReply(257, context);
	cmdmgr->sendReply(258, context);
	cmdmgr->sendReply(259, context);
	(void)args;
}