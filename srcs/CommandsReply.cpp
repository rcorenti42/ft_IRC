/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/23 23:56:33               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   CommandsReply.cpp                                                        */
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
	return "irc.UTK.org 420 woisx inpstmcqaovlbkSR";
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

std::string	RPL_TIME(std::string time) {
	return "UTK:" + time;
};

std::string	ERR_NOORIGIN() {
	return ":No origin specified";
};

std::string	ERR_NONICKNAMEGIVEN() {
	return ":No nickname given";
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