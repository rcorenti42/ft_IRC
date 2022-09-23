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
	return ":Your host is 42, running version 420";
};

std::string	RPL_CREATED() {
	return ":This server was created 4 may at 2042, 00:42:42";
};

std::string	RPL_MYINFO() {
	return "irc.42.org 420 woisx inpstmcqaovlbkSR";
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