/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsReply.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/27 19:20:23 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "CommandsReply.hpp"

std::string	RPL_WELCOME(std::string nick, std::string user, std::string addr) {
	return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + addr;
};

std::string	RPL_YOURHOST() {
	return ":Your host is UTK, running version 420";
};

std::string	RPL_CREATED() {
	return ":This server was created 4 may at 2042, 00:42:42";
};

std::string	RPL_MYINFO() {
	return "IR-C4 420 woisx inpstmcqaovlbkSR";
};

std::string	RPL_UMODEIS(std::string usermodes) {
	return usermodes;
};

std::string	RPL_LUSERCLIENT(std::string invisiblesClientsNbr, std::string noInvisiblesClientsNbr) {
	return ":There are " + noInvisiblesClientsNbr + " users and " + invisiblesClientsNbr + " invisible on 1 servers";
};

std::string	RPL_LUSEROP(std::string operatorsNbr) {
	return operatorsNbr + " :operator(s) online";
};

std::string	RPL_LUSERUNKNOWN(std::string unknownClients) {
	return unknownClients + " :unknown connection(s)";
};

std::string	RPL_LUSERCHANNELS(std::string channelsNbr) {
	return channelsNbr + " :channels formed";
};

std::string	RPL_LUSERME(std::string clientsNbr) {
	return ":I have " + clientsNbr + " clients and 1 servers";
};

std::string	RPL_CHANNELMODEIS(std::string channel, std::string mode, std::string arg) {
	return channel + " " + mode + " " + arg;
};

std::string	RPL_NOTOPIC(std::string channel) {
	return channel + " :No topic is set";
};

std::string	RPL_TOPIC(std::string channel, std::string topic) {
	return channel + " :" + topic;
};

std::string	RPL_BANLIST(std::string channel, std::string banmask) {
	return channel + " " + banmask;
};

std::string	RPL_ENDOFBANLIST(std::string channel) {
	return channel + " :End of channel ban list";
};

std::string RPL_INFO(std::string output) {
	return output;
}

std::string RPL_ENDOFINFO(){
	return "End of /info LIST";	
}

std::string	RPL_TIME(std::string time) {
	return "UTK:" + time;
};

std::string	ERR_NOSUCHNICK(std::string name) {
	return name + " :No such nick/channel";
};

std::string	ERR_NOSUCHCHANNEL(std::string channel) {
	return channel + " :No such channel";
};

std::string	ERR_NOORIGIN() {
	return ":No origin specified";
};

std::string	ERR_NONICKNAMEGIVEN() {
	return ":No nickname given";
};

std::string	ERR_NOTONCHANNEL(std::string channel) {
	return channel + " :You're not on that channel";
};

std::string	ERR_NEEDMOREPARAMS(std::string cmd) {
	return cmd + " :Not enough parameters";
};

std::string	ERR_ALREADYREGISTERED() {
	return ":You may not reregister";
};

std::string	ERR_PASSWDMISMATCH() {
	return ":Password incorrect";
};

std::string	ERR_KEYSET(std::string channel) {
	return channel + " :Channel key already set";
};

std::string	ERR_UNKNOWNMODE(std::string c) {
	return c + " :is unknown mode char to me";
};

std::string	ERR_BADCHANMASK(std::string channel) {
	return channel + " :The given channel mask was invalid";
};

std::string	ERR_CHANOPRIVSNEEDED(std::string channel) {
	return channel + " :You're not channel operator";
};

std::string	ERR_UMODEUNKNOWNFLAG() {
	return ":Unknown MODE flag";
};

std::string	ERR_USERSDONTMATCH() {
	return ":Cant change mode for other users";
};