/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:05 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/03 16:26:39 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CommandManager.hpp>
CommandManager *CommandManager::_instance = 0;

CommandManager::CommandManager() {
	replies[1] = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
	replies[2] = "Your host is <servername>, running version <version>";
	replies[3] = "This server was created <date_of_creation>";
	replies[4] = "<server_name> <version> <user_modes> <chan_modes>";
	replies[221] = "<user_modes> [<user_mode_params>]";
	replies[251] = "There are <nbusers> users and <nbinvis> invisible on 1 servers";
	replies[252] =	"<nboperators> : operators online";
	replies[253] =	"<nbunk> : unknown connections";
	replies[254] = "<nbchan> : channels formed";
	replies[255] = "I have <nbclients> clients and 1 servers";
	replies[324] = "<channel> <mode> <mode_params>";
	replies[331] = "<channel> : No topic is set";
	replies[332] = "<channel> : <topic>";
	replies[367] = "<channel> <banid> [<time_left> :<reason>]";
	replies[368] = "<channel> : End of channel ban list";
	replies[371] = "<info>";
	replies[374] = "End of /info list";
	replies[391] =	"<server_name> : <time>";
	replies[401] = "<string> : No such nick";
	replies[403] = "<string> : No such channel";
	replies[409] = "No origin specified";
	replies[431] = "No nickname given";
	replies[442] = "<channel> : You're not on that channel";
	replies[461] = "<string> : Not enough parameters";
	replies[464] = "Password incorrect";
	replies[467] = "<channel> : Channel key already set";
	replies[472] = "<string> : Is unknown mod char to me";
	replies[476] = "<channel> : The given channel mask was invalid";
	replies[482] = "<channel> : You're not a channel operator";
	replies[501] = "Unknown mode flag";
	replies[502] = "Can't change mode for other users";
}

static void	string_replace(string &str, const string &substr, const string &repl)
{
	size_t pos = str.find(substr);
	if (pos == string::npos) return;
	str.replace(pos, substr.length(), repl);
}

string CommandManager::getReply(int code, Context context)
{
	string command = replies[code];
	string_replace(command, "<nick>", context.client->getNickname()); //and so on for every <markup>

	return command;
}

CommandManager *CommandManager::getInstance() {
	if (!_instance) _instance = new CommandManager();
	return _instance;
}
