/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:05 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/21 10:43:01 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CommandManager.hpp>

CommandManager *CommandManager::_instance = 0;

CommandManager::CommandManager() {
	replies[1] = ":Welcome to the <network> Network <nickname>";
	replies[2] = ":Your host is <servername>, running version <version>";
	replies[3] = ":This server was created <datetime>";
	replies[4] = "<servername> <version> <umodes> <cmodes>";
	replies[221] = "<user_mode>";
	replies[251] = ":There are <nbnoinvisibles> users and <nbinvisibles> invisible on <nbservers> servers";
	replies[252] =	"<nbuoperators> :operators online";
	replies[253] =	"<nbunknown> :unknown connections";
	replies[254] = "<nbchannels> :channels formed";
	replies[255] = ":I have <nbclients> clients and 1 servers";
	replies[256] = "<servername> :Administrative info";
	replies[257] = "Server irc.ir-c4.org";
	replies[258] = "Website www.ir-c4.org";
	replies[259] = "Mail admin@ir-c4.org";
	replies[321] = "Channel :Users Name";
	replies[322] = "<channel> <nbVisiblesOnChannels> :<chanTopic>";
	replies[323] = ":End of /LIST";
	replies[324] = "<channel> <channel_mode>";
	replies[331] = "<info> :No topic is set";
	replies[332] = "<channel> :<topic>";
	replies[341] = "<channel> <nickname>";
	replies[351] = "<version>.0 <servername>:IR-C4";
	replies[353] = "= <channel> :<namelist>";
	replies[366] = "<channel> :End of /NAMES list";
	replies[367] = "<channel> <banid>";
	replies[368] = "<channel> :End of channel ban list";
	replies[371] = "<info>";
	replies[374] = "End of /INFO list";
	replies[381] = ":You are now an IRC operator";
	replies[401] = "<nickname> :No such nick";
	replies[403] = "<info> : No such channel";
	replies[404] = "<channel> :Cannot send to channel";
	replies[409] = ":No origin specified";
	replies[431] = ":No nickname given";
	replies[433] = "* <args> :Nickname is already in use";
	replies[442] = "<channel> :You're not on that channel";
	replies[443] = "<nickname> <channel> :is already on channel";
	replies[461] = "<command> :Not enough parameters";
	replies[462] = ":You may not reregister";
	replies[464] = ":Password incorrect";
	replies[467] = "<channel> :Channel key already set";
	replies[472] = "<info> :is unkwown char to me.";
	replies[473] = "<channel> :Cannot join channel (+i)";
	replies[476] = "<channel> :The given channel mask was invalid";
	replies[481] = ":Permission Denied - You're not an IRC operator";
	replies[482] = "<channel> :You're not a channel operator";
	replies[501] = ":Unknown MODE flag";
	replies[502] = ":Can't change mode for other users";

	_listCommands["LIST"] = LIST;
	_listCommands["INFO"] = INFO;
	_listCommands["PASS"] = PASS;
	_listCommands["NICK"] = NICK;
	_listCommands["USER"] = USER;
	_listCommands["MOTD"] = MOTD;
	_listCommands["LUSERS"] = LUSERS;
	_listCommands["PING"] = PING;
	_listCommands["PONG"] = PONG;
	_listCommands["MODE"] = MODE;
	_listCommands["JOIN"] = JOIN;
	_listCommands["ISON"] = ISON;
	_listCommands["PRIVMSG"] = PRIVMSG;
	_listCommands["NOTICE"] = NOTICE;
	_listCommands["PART"] = PART;
	_listCommands["TOPIC"] = TOPIC;
	_listCommands["QUIT"] = QUIT;
	_listCommands["OPER"] = OPER;
	_listCommands["VERSION"] = VERSION;
	_listCommands["KICK"] = KICK;
	_listCommands["INVITE"] = INVITE;
	_listCommands["WALLOPS"] = WALLOPS;
	_listCommands["DIE"] = DIE;
	_listCommands["KILL"] = KILL;
	_listCommands["ADMIN"] = ADMIN;
	_listCommands["NAMES"] = NAMES;
}

static void	string_replace(string &str, const string &substr, const string &repl)
{
	size_t pos = str.find(substr);
	if (pos == string::npos) return;
	str.replace(pos, substr.length(), repl);
}

static void	string_replace(string &str, const string &substr, size_t repl)
{
	std::ostringstream ss;
	ss << repl;

	size_t pos = str.find(substr);
	if (pos == string::npos) return;
	str.replace(pos, substr.length(), ss.str());
}

string 	&strcap(string &str) {
	for (string::iterator it = str.begin(); it != str.end(); ++it)
		*it = std::toupper(*it);
	return str;
}

void	CommandManager::parsePacket(const string &packet, Command *result, std::vector<string> &arg_vec) {
	size_t pos = 0;
	string cpy;

	cpy = packet;
	pos = cpy.find(":", pos + 1);
	if (pos != string::npos)
	{
		result->message = cpy.substr(pos + 1);
		cpy.erase(pos);
	}
	pos = -1;
	do {
		cpy.erase(0, pos + 1);
		pos = cpy.find(" ");
		if (pos != 1)
			arg_vec.push_back(cpy.substr(0, pos));
	} while (pos != string::npos);
	arg_vec.push_back("");
	result->id = strcap(arg_vec[0]);
	result->args =  &(arg_vec[1]);
}

static bool	isAllowed(Client &client, string &command)
{
	if (command == "PASS") return true;
	if (client.getStats() == CONNECTED) return false;
	if (command == "NICK" || command == "USER") return true;
	if (client.getStats() == CHECKPASS) return false;
	return true;
}

void    CommandManager::registerClient(Client &client, Context &context) {
	client.setState(REGISTERED);
    client.writePrefixMsg(1, getReply(1, context));
	client.writePrefixMsg(2, getReply(2, context));
	client.writePrefixMsg(3, getReply(3, context));
	client.writePrefixMsg(4, getReply(4, context));
	LUSERS(context, 0);
	MOTD(context, 0);
}

void	CommandManager::execute(string &packet, Client &client) {
	Command command;
	std::vector<string> vec;
	Context context;

	parsePacket(packet, &command, vec);
	if (!isAllowed(client, command.id)) return;
	context.client = &client;
	context.message = &command.message;
	context.packet = &packet;
	context.channel = NULL;
	context.info = NULL;
	context.args = NULL;
	if (_listCommands.find(command.id) == _listCommands.end()) return;
	_listCommands[command.id](context, command.args);
	if (client.getStats() == CHECKPASS && !client.getNickname().empty())
		registerClient(client, context);
}

string CommandManager::getReply(int code, Context context)
{
	Server *serv = Server::getInstance();
	string command = replies[code];
	string_replace(command, "<network>", "IR-C4");
	string_replace(command, "<nickname>", context.client->getNickname());
	string_replace(command, "<args>", *context.args);
	string_replace(command, "<servername>", "irc.ir-c4.org");
	string_replace(command, "<version>", "420");
	string_replace(command, "<datetime>", serv->getInstance()->getStartTime());
	string_replace(command, "<umodes>", "is");
	string_replace(command, "<cmodes>", "Ooinpstmv");
	string_replace(command, "<user_mode>", context.client->getMode());
	string_replace(command, "<nbnoinvisibles>", serv->getVisibleNbr());
	string_replace(command, "<nbinvisibles>", serv->getInvisNbr());
	string_replace(command, "<nbservers>", "1");
	string_replace(command, "<nbuoperators>", serv->getOPNbr());
	string_replace(command, "<nbunknown>", serv->getUnknbr());
	string_replace(command, "<nbchannels>", serv->getChanNbr());
	string_replace(command, "<nbclients>", serv->getUsrNbr());
	if (context.channel)
	{
		string_replace(command, "<nbVisiblesOnChannels>", context.channel->getVisiblesNbr());
		string_replace(command, "<chanTopic>", context.channel->getTopic());
		string_replace(command, "<channel>", context.channel->getName());
		string_replace(command, "<channel_mode>", context.channel->getMode());
		string_replace(command, "<topic>", context.channel->getTopic());
		string_replace(command, "<namelist>", *context.args);
	}
	if (context.info)
		string_replace(command, "<info>", *context.info);
	if (context.args)
		string_replace(command, "<command>", *context.args);
	return " " + command;
}

CommandManager *CommandManager::getInstance() {
	if (!_instance) _instance = new CommandManager();
	return _instance;
}

void CommandManager::sendReply(int code, Context context) {
	context.client->writePrefixMsg(code, getReply(code, context));
}

CommandManager::CommandException::CommandException(const string &what) : _what(what) {}
const char *CommandManager::CommandException::what() const throw() {return _what.c_str();}
