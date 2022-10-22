/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/22 13:28:25 by lothieve         ###   ########.fr       */
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

	if (context.client->getStats() == CHECKPASS || context.client->getStats() == REGISTERED)
		cmdmgr->sendReply(462, context);
	else if (*args == Server::getInstance()->getPassword())
		context.client->setState(CHECKPASS);
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

	(void)args;
	if (context.message->empty())
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
	if (!context.message)
		cmdmgr->sendReply(409, context);
	else
		context.client->setPing(std::time(NULL));
	(void)args;
}

void	MOTD(Context &context, string *args) {
	string	message = " - IR-C4 Message of the Day -\r\n";
	message += "- Welcome to IR-C4 Server !\r\n-\r\n-\r\n";
	// message += "-       ,---,,-.----.\r\n";
	// message += "-    ,`--.' |\\    /  \\\r\n";
	// message += "-    |   :  :;   :    \\\r\n";
	// message += "-    :   |  '|   | .\\ :\r\n";
	// message += "-    |   :  |.   : |: |\r\n";
	// message += "-    '   '  ;|   |  \\ :\r\n";
	// message += "-    |   |  ||   : .  /\r\n";
	// message += "-    '   :  ;;   | |  \\\r\n";
	// message += "-    |   |  '|   | ;\\  \\\r\n";
	// message += "-    '   :  |:   ' | \\.'\r\n";
	// message += "-    ;   |.' :   : :-'\r\n";
	// message += "-    '---'   |   |.'\r\n";
	// message += "-            `---'\r\n";
	// message += "-        ,---,.   ,---,.\r\n";
	// message += "-      ,'  .' | ,'  .' |\r\n";
	// message += "-    ,---.'   ,---.'   ,\r\n";
	// message += "-    |   |    |   |    |\r\n";
	// message += "-    :   :  .':   :  .'\r\n";
	// message += "-    :   |.'  :   |.'\r\n";
	// message += "-    `---'    `---'     ,--,\r\n";
	// message += "-      ,----..        ,--.'|\r\n";
	// message += "-     /   /   \\    ,--,  | :\r\n";
	// message += "-    |   :     :,---.'|  : '\r\n";
	// message += "-    .   |  ;. /;   : |  | ;\r\n";
	// message += "-    .   ; /--` |   | : _' |\r\n";
	// message += "-    ;   | ;    :   : |.'  |\r\n";
	// message += "-    |   : |    |   ' '  ; :\r\n";
	// message += "-    .   | '___ \\   \\  .'. |\r\n";
	// message += "-    '   ; : .'| `---`:  | '\r\n";
	// message += "-    '   | '/  :      '  ; |\r\n";
	// message += "-    |   :    /       |  : ;\r\n";
	// message += "-     \\   \\ .'        '  ,/\r\n";
	// message += "-      `---`          '--'\r\n-\r\n-\r\n";
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
	int mode = 1;
	size_t pos;

	if (modestring[0] == '-') {
		mode = 0;
		modestring.erase(0, 1);
	}
	else if (modestring[0] == '+')
		modestring.erase(0, 1);
	while ((pos = modestring.find_first_not_of("iw")) != string::npos)
	{
		string character(1, modestring[pos]);
		context.info = &character;
		modestring.erase(pos, 1);
		cmdmgr->sendReply(472, context);
	}
	if (modestring.empty())
		return;
	if (mode == 0)
		context.client->removeMode(modestring);
	else if (mode == 1)
		context.client->addMode(modestring);
	cmdmgr->sendReply(221, context);
}

void	argMode(Context &context, string *args, string modestring, int mode)
{
	size_t i = 2;
	size_t pos = modestring.find_first_of("ov");
	Client *client;
	while (pos != string::npos)
	{
		try { client = &Server::getInstance()->findClient(args[i]);}
		catch(Server::ClientNotFoundException &e) { return;}
		if (mode == 0)
		{
			if (modestring[pos] == 'o')
			{
				context.channel->removeOperator(*client);
				context.channel->broadcastMessage(*context.client, "MODE " + context.channel->getName() + " -o :" + client->getNickname());
			}
			else if (modestring[pos] == 'v')
			{
				context.channel->removeVerbose(*client);
				context.channel->broadcastMessage(*context.client, "MODE " + context.channel->getName() + " -v :" + client->getNickname());
			}
		}
		else if (mode == 1)
		{
			if (modestring[pos] == 'o')
			{
				context.channel->addOperator(*client);
				context.channel->broadcastMessage(*context.client, "MODE " + context.channel->getName() + " +o :" + client->getNickname());
			}
			else if (modestring[pos] == 'v')
			{
//>>>>>>> refs/remotes/origin/main
				context.channel->addVerbose(*client);
				context.channel->broadcastMessage(*context.client, "MODE " + context.channel->getName() + " +v :" + client->getNickname());
			}
		}
		modestring.erase(pos, 1);
		pos = modestring.find_first_of("ov");
		i++;
	}
		
}

int		psModes(Context& context, string modestring, int mode, string& ret) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	size_t			pos = modestring.find_last_of("ps");
	if (mode) {
		if (modestring[pos] == 'p') {
			if (context.channel->isSecret()) {
				if (!context.channel->isOperator(context.client->getNickname()))
					cmdmgr->sendReply(482, context);
				else {
					ret += 'p';
					ret.erase(ret.find('s'), 1);
					mode = 2;
				}
			}
			else if (!context.channel->isPrivate()) {
				if (!context.channel->isOperator(context.client->getNickname()))
					cmdmgr->sendReply(482, context);
				else {
					ret += 'p';
					mode = 2;
				}
			}
		} else {
			if (context.channel->isPrivate()) {
				if (!context.channel->isOperator(context.client->getNickname()))
					cmdmgr->sendReply(482, context);
				else {
					ret += 's';
					ret.erase(ret.find('p'), 1);
					mode = 2;
				}
			} else if (!context.channel->isSecret()) {
				if (!context.channel->isOperator(context.client->getNickname()))
					cmdmgr->sendReply(482, context);
				else {
					ret += 's';
					mode = 2;
				}
			}
		}
	} else {
		if (modestring[pos] == 'p') {
			if (!context.channel->isOperator(context.client->getNickname()))
				cmdmgr->sendReply(482, context);
			else if (context.channel->isPrivate()) {
				mode = 2;
				ret.erase(ret.find('p'), 1);
			}
		} else {
			if (!context.channel->isOperator(context.client->getNickname()))
				cmdmgr->sendReply(482, context);
			else if (context.channel->isSecret()) {
				mode = 2;
				ret.erase(ret.find('s'), 1);
			}
		}
	}
	return mode;
};

void	channelMode(Context &context, string modestring, string *args) //ecrire un message MODE a tout les clients dans le channel
{
	string ret = context.channel->getMode();
	bool isOp = context.channel->isOperator(context.client->getNickname());
	CommandManager *cmdmgr = CommandManager::getInstance();
	string flgs = "inpstmov";
	int mode = 1;
	size_t pos;

	if (modestring[0] == '-') {
		mode = 0;
		modestring.erase(0, 1);
	}
	else if (modestring[0] == '+')
		modestring.erase(0, 1);
	while ((pos = modestring.find_first_not_of(flgs)) != string::npos)
	{
		string character(1, modestring[pos]);
		context.info = &character;
		modestring.erase(pos, 1);
		cmdmgr->sendReply(472, context);
	}
	if (mode == 0)
	{
		flgs = "intm";
		for (size_t i = 0; i < flgs.size(); i++)
		{
			if (modestring.find(flgs[i]) != string::npos && (ret.find(flgs[i]) != string::npos))
			{
				if (!isOp)
					cmdmgr->sendReply(482, context);
				else
				{
					mode = 2;
					ret.erase(ret.find(flgs[i]), 1);
				}
			}
		}
	}
	else if (mode == 1)
	{
		flgs = "intm";
		for (size_t i = 0; i < flgs.size(); i++)
		{
			if (modestring.find(flgs[i]) != string::npos && ret.find(flgs[i]) == string::npos)
			{
				if (!isOp)
					cmdmgr->sendReply(482, context);
				else
				{
					ret += flgs[i];
					mode = 2;
				}
			}
		}
	}
	mode = psModes(context, modestring, mode, ret);
	argMode(context, args, modestring, mode);
	context.channel->setMode(ret);
	if (mode == 2)
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
		if (args[1].empty())
			cmdmgr->sendReply(324, context);
		else
			channelMode(context, args[1], args);
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
		else if (args[1].empty())
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
	int 				start = 0;
	int 				end;
	bool				isInvit;
	string				baseModes = "tn";
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
		isInvit = true;
		if ((*it)[0] != '#' && (*it)[0] != '&')
			cmdmgr->sendReply(476, context);
		else {
			Channel& channel = Server::getInstance()->getChannel(*it);
			context.channel = &channel;
			if (channel.isEmpty()) {
				channel.setMode(baseModes);
				channel.addOperator(*context.client);
			}
			else if (channel.getMode().find('i') != string::npos) {
				if (channel.isInvited(context.client->getNickname()))
					channel.removeInvit(*context.client);
				else
					isInvit = false;
			}
			if (isInvit) {
				channel.addClient(*context.client);
				if (!channel.getTopic().empty())
					cmdmgr->sendReply(332, context);
				channel.broadcastMessage(*context.client, "JOIN :" + channel.getName());
				cmdmgr->sendReply(366, context);
			}
			else
				cmdmgr->sendReply(473, context);
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
	do {
		end = args->find(',', start);
		string arg = args->substr(start, end - start);
		if (arg[0] == '#' || arg[0] == '&')
			channels.push_back(arg);
		else
			clients.push_back(arg);
		start = end + 1;

	} while (end != -1);
	for (std::vector<string>::iterator it = channels.begin(); it != channels.end(); it++) {
		try {
		Channel&				chan = Server::getInstance()->findChannel(*it);
		std::vector<Client*>	cli = chan.getClients();
		context.channel = &chan;
		for (std::vector<Client*>::iterator iter = cli.begin(); iter != cli.end(); iter++)
			if ((*iter)->getNickname() != context.client->getNickname() && (!chan.isModerate() || context.client->isVerbose(&chan) || chan.isOperator(context.client->getNickname())))
				context.client->writePrefixMsg(**iter, "PRIVMSG " + *it + " :" + *context.message);
			else if (!context.client->isVerbose(&chan) && chan.isModerate() && (*iter)->getNickname() != context.client->getNickname())
				cmdmgr->sendReply(404, context);
		} catch (Server::ChannelNotFoundException &e) {cmdmgr->sendReply(403, context);}
	}
	for (std::vector<string>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		try {
			context.client->writePrefixMsg(Server::getInstance()->findClient(*it), "PRIVMSG " + context.client->getUsername() + " :" + *context.message);
		} catch (Server::ClientNotFoundException &e) {cmdmgr->sendReply(403, context);}
	}
};

//copier coller de la fonction PRIVMSG sans les reply.
void	NOTICE(Context& context, string* args) {
	int							start = 0;
	int							end;
	std::vector<string>	channels;
	std::vector<string>	clients;
	if (!args || args->empty() || !context.message || context.message->empty())
		return ;
	do {
		end = args->find(',', start);
		string arg = args->substr(start, end - start);
		if (arg[0] == '#' || arg[0] == '&')
			channels.push_back(arg);
		else
			clients.push_back(arg);
		start = end + 1;

	} while (end != -1);
	for (std::vector<string>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel&				chan = Server::getInstance()->getChannel(*it);                                                                                                    
		std::vector<Client*>	cli = chan.getClients();
		context.channel = &chan;
		for (std::vector<Client*>::iterator iter = cli.begin(); iter != cli.end(); iter++)
			if ((*iter)->getNickname() != context.client->getNickname() && (!chan.isModerate() || context.client->isVerbose(&chan) || chan.isOperator(context.client->getNickname())))
				(*iter)->writePrefixMsg("PRIVMSG " + *it + " :" + *context.message);
	}
	for (std::vector<string>::iterator it = clients.begin(); it != clients.end(); it++)
		context.client->writePrefixMsg(Server::getInstance()->findClient(*it), "PRIVMSG " + context.client->getUsername() + " :" + *context.message);
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
 	try {context.channel = &Server::getInstance()->findChannel(*args);}
	catch (Server::ChannelNotFoundException &e)
	{
		context.info = args;
		cmdmgr->sendReply(403, context);
		return ;
	}
	if (context.channel->isClient(*context.client) == 0)
	{
		cmdmgr->sendReply(442, context);
		return ;
	}
	if (!context.message || context.message->empty())
	{
		if (context.channel->getTopic().empty())
			cmdmgr->sendReply(331, context);
		else	
			cmdmgr->sendReply(332, context);
		return ;
	}
	if (context.channel->getMode().find('t') != string::npos && !context.channel->isOperator(context.client->getNickname())) {
			cmdmgr->sendReply(482, context);
			return ;	
	}
	else {
		context.channel->setTopic(*context.message);
		context.channel->broadcastMessage(*context.client, "TOPIC " + context.channel->getName() + " :" + *context.message);
	}
};

void	OPER(Context &context, string *args) {
	std::map<string, string>	operators;
	operators["rcorenti"] = "stickos";
	operators["sobouatt"] = "1234";
	operators["lothieve"] = "kamazdelinfini";
	CommandManager *cmdmgr = CommandManager::getInstance();
	if (!args || args->empty() || args[1].empty()) {
		cmdmgr->sendReply(461, context);
		return ;
	}
	for (std::map<string, string>::iterator it = operators.begin(); it != operators.end(); ++it)
		if ((*it).first == *args && (*it).second == args[1]) {
			cmdmgr->sendReply(381, context);
			context.client->setOperServ(true);
			return ;
		}
	cmdmgr->sendReply(464, context);
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
	CommandManager*			cmdmgr = CommandManager::getInstance();
	std::vector<Channel*>	channels = Server::getInstance()->getChannels();
	if (args->empty() || !args) {
		for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
			if ((*it)->isOn(context.client->getSocket())) {
				*context.args = (*it)->getClientsList();
				cmdmgr->sendReply(353, context);
			}
			else if (!(*it)->isPrivate() && !(*it)->isSecret()) {
				*context.args = (*it)->getClientsListOut();
				cmdmgr->sendReply(353, context);
			}
		}
	}
	else {
		try {context.channel = &Server::getInstance()->findChannel(*args);}
		catch (Server::ChannelNotFoundException& e) {return;}
			if ((context.channel)->isOn(context.client->getSocket())) {
				*context.args = (context.channel)->getClientsList();
				cmdmgr->sendReply(353, context);
			}
			else if (!(context.channel)->isPrivate() && !(context.channel)->isSecret()) {
				*context.args = (context.channel)->getClientsListOut();
				cmdmgr->sendReply(353, context);
			}
	}
	cmdmgr->sendReply(366, context);
};

void	ADMIN(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	cmdmgr->sendReply(256, context);
	cmdmgr->sendReply(257, context);
	cmdmgr->sendReply(258, context);
	cmdmgr->sendReply(259, context);
	(void)args;
};

void	LIST(Context& context, string* args)
{
	std::vector<Channel*>	chan = Server::getInstance()->getChannels();
	CommandManager*			cmdmgr = CommandManager::getInstance();
	cmdmgr->sendReply(321, context);
	if (args->empty()) {
		for (std::vector<Channel*>::iterator it = chan.begin(); it != chan.end(); ++it) {
			context.channel = *it;
			if ((*it)->getMode().find('s') == string::npos && (*it)->getMode().find('p') == string::npos)
				cmdmgr->sendReply(322, context);
		}
	} else {
		context.channel = &Server::getInstance()->getChannel(*args);
		if (Server::getInstance()->getChannel(*args).getTopic().empty())
			cmdmgr->sendReply(331, context);
		else
			cmdmgr->sendReply(332, context);
		return ;
	}
	cmdmgr->sendReply(323, context);
};

void	INVITE(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	context.args = args;
	try {
		context.channel = &Server::getInstance()->findChannel(args[1]);
	} catch (Server::ChannelNotFoundException& e) {
		cmdmgr->sendReply(442, context);
		return;
	}
	*context.message = "Inviting " + *args + " in channel " + args[1] + " ...";
	if (!args || args->empty()) {
		cmdmgr->sendReply(461, context);
		return;
	}
	try {
		Server::getInstance()->findClient(*args);
	} catch (Server::ClientNotFoundException& e) {
		cmdmgr->sendReply(401, context);
		return;
	}
	if (context.channel->getClientsMap().find(context.client->getSocket()) == context.channel->getClientsMap().end()) {
		cmdmgr->sendReply(442, context);
		return;
	}
	if (Server::getInstance()->getChannel(args[1]).isClient(*Server::getInstance()->getClient(*args))) {
		cmdmgr->sendReply(443, context);
		return;
	}
	if (!Server::getInstance()->getChannel(args[1]).isOperator(context.client->getNickname())) {
		cmdmgr->sendReply(482, context);
		return;
	}
	cmdmgr->sendReply(341, context);
	NOTICE(context, args + 1);
	context.client->writePrefixMsg(Server::getInstance()->findClient(*args), *context.packet);
	Server::getInstance()->findChannel(args[1]).addInvit(*Server::getInstance()->getClient(*args));
};

void	WALLOPS(Context& context, string* args) {
	CommandManager*			cmdmgr = CommandManager::getInstance();
	std::vector<Client*>	clientsList = Server::getInstance()->getClients();
	if (!context.message || context.message->empty()) {
		cmdmgr->sendReply(461, context);
		return ;
	}
	for (std::vector<Client*>::iterator it = clientsList.begin(); it != clientsList.end(); it++)
		if ((*it)->getNickname() != context.client->getNickname() && (*it)->getOperServ() && (*it)->getMode().find('w') != string::npos)
			context.client->writePrefixMsg(*(*it), "WALLOPS :" + *context.message);
	(void)args;
};

void	DIE(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	if (context.client->getOperServ())
		Server::getInstance()->killServ();
	else
		cmdmgr->sendReply(481, context);
	(void)args;
};

void	KILL(Context& context, string* args) {
	CommandManager*	cmdmgr = CommandManager::getInstance();
	if (!context.message || context.message->empty() || !args || args->empty()) {
		cmdmgr->sendReply(461, context);
		return ;
	}
	if (!Server::getInstance()->getClient(*args)) {
		cmdmgr->sendReply(401, context);
		return ;
	}
	if (context.client->getOperServ())
		Server::getInstance()->getClient(*args)->setState(NONE);
	else
		cmdmgr->sendReply(481, context);
};
