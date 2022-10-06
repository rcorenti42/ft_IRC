/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:05 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/06 23:07:15 by sobouatt         ###   ########.fr       */
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
	replies[324] = "<channel> <channel_mode>";
	replies[331] = "<channel> :No topic is set";
	replies[332] = "<channel> :<topic>";
	replies[351] = "<version>.0 <servername>:IR-C4";
	replies[353] = "<channel> : <namelist>";
	replies[366] = "<channel> :End of /NAMES list";
	replies[367] = "<channel> <banid>";
	replies[368] = "<channel> :End of channel ban list";
	replies[371] = "<info>";
	replies[374] = "End of /info list";
	replies[401] = "<nickname> :No such nick";
	replies[403] = "<info> : No such channel";
	replies[409] = ":No origin specified";
	replies[431] = ":No nickname given";
	replies[442] = "<channel> :You're not on that channel";
	replies[461] = "<command> :Not enough parameters";
	replies[464] = ":Password incorrect";
	replies[467] = "<channel> :Channel key already set";
	replies[472] = "<info> : Is unknown mod char to me";
	replies[476] = "<channel> :The given channel mask was invalid";
	replies[482] = "<channel> :You're not a channel operator";
	replies[501] = ":Unknown MODE flag";
	replies[502] = ":Can't change mode for other users";
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

string CommandManager::getReply(int code, Context context)
{
	Server *serv = Server::getInstance();
	string command = replies[code];
	string_replace(command, "<network>", "IR-C4");
	string_replace(command, "<nickname>", context.client->getNickname());
	string_replace(command, "<servername>", "irc.ir-c4.org");
	string_replace(command, "<version>", "420");
	string_replace(command, "<datetime>", "4 may at 2042, 00:42:42");
	string_replace(command, "<umodes>", "is");
	string_replace(command, "<cmodes>", "opsitnmlbvk");
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
		string_replace(command, "<channel>", context.channel->getName());
		string_replace(command, "<channel_mode>", context.channel->getMode());
		string_replace(command, "<topic>", context.channel->getTopic());
		string_replace(command, "<namelist>", context.channel->getClientsList());
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

