/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/21 03:25:10               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   Commands.cpp                                                             */
/* ************************************************************************** */

#include "Commands.hpp"
#include "CommandsRet.hpp"
#include "CommandsReply.hpp"
#include "Client.hpp"
#include "Server.hpp"

Commands::Commands(std::string str) //constructor for testing purpose
{
	size_t pos;
	if ((pos = str.find(":")) != std::string::npos) {
		this->_message = str.substr(pos + 1);
		str.erase(pos);
	}
	while ((pos = str.find(" ")) != std::string::npos) {
		this->_args.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}
	this->_args.push_back(str);
	this->_command = *(this->_args.begin());
	for (size_t i = 0; i < this->_command.length(); i++)
		this->_command[i] = std::toupper(this->_command[i]);
	this->_args.erase(this->_args.begin());
	std::cout << "command : " << this->_command << std::endl;
	std::cout << "args : {";
	for (std::vector<std::string>::iterator it = this->_args.begin(); it != this->_args.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << "}" << std::endl;
	std::cout << "message : " << this->_message;
}
Commands::Commands(Client *client, Server *server, std::string str) : _client(client), _server(server)
{
	size_t pos;
	if ((pos = str.find(":")) != std::string::npos) {
		this->_message = str.substr(pos + 1);
		str.erase(pos);
	}
	while ((pos = str.find(" ")) != std::string::npos) {
		this->_args.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}
	this->_args.push_back(str);
	this->_command = *(this->_args.begin());
	for (size_t i = 0; i < this->_command.length(); i++)
		this->_command[i] = toupper(this->_command[i]);
	this->_args.erase(this->_args.begin());
	std::cout << "command : " << this->_command << std::endl;
	std::cout << "args : {";
	for (std::vector<std::string>::iterator it = this->_args.begin(); it != this->_args.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << "}" << std::endl;
	std::cout << "message : " << this->_message;
}
std::string					Commands::getCommand() const {
	return this->_command;
};
std::string					Commands::getMessage() const {
	return this->_message;
};
std::vector<std::string>	Commands::getArgs() const {
	return this->_args;
};
Client*						Commands::getClient() const {
	return this->_client;
};
Server*						Commands::getServer() const {
	return this->_server;
};
std::string					Commands::sendRep(int code, std::string arg1, std::string arg2, std::string arg3) {
	switch (code) {
	case 1:
		return " 001 " + this->_client->getNickname() + " " + RPL_WELCOME(this->_client->getNickname(), this->_client->getUsername(), this->_client->getAddr());
	case 2:
		return " 002 " + this->_client->getNickname() + " " + RPL_YOURHOST();
	case 3:
		return " 003 " + this->_client->getNickname() + " " + RPL_CREATED();
	case 4:
		return " 004 " + this->_client->getNickname() + " " + RPL_MYINFO();
	case 221:
		return " 221 " + this->_client->getNickname() + " " + RPL_UMODEIS(arg1);
	case 251:
		return " 251 " + this->_client->getNickname() + " " + RPL_LUSERCLIENT(arg1, arg2);
	case 252:
		return " 252 " + this->_client->getNickname() + " " + RPL_LUSEROP(arg1);
	case 253:
		return " 253 " + this->_client->getNickname() + " " + RPL_LUSERUNKNOWN(arg1);
	case 254:
		return " 254 " + this->_client->getNickname() + " " + RPL_LUSERCHANNELS(arg1);
	case 255:
		return " 255 " + this->_client->getNickname() + " " + RPL_LUSERME(arg1);
	case 324:
		return " 324 " + this->_client->getNickname() + " " + RPL_CHANNELMODEIS(arg1, arg2, arg3);
	case 367:
		return " 367 " + this->_client->getNickname() + " " + RPL_BANLIST(arg1, arg2);
	case 368:
		return " 368 " + this->_client->getNickname() + " " + RPL_ENDOFBANLIST(arg1);
	case 391:
		return " 391 " + this->_client->getNickname() + " " + RPL_TIME(arg1);
	case 401:
		return " 401 " + this->_client->getNickname() + " " + ERR_NOSUCHNICK(arg1);
	case 403:
		return " 403 " + this->_client->getNickname() + " " + ERR_NOSUCHCHANNEL(arg1);
	case 409:
		return " 409 " + this->_client->getNickname() + " " + ERR_NOORIGIN();
	case 431:
		return " 431 " + this->_client->getNickname() + " " + ERR_NONICKNAMEGIVEN();
	case 442:
		return " 442 " + this->_client->getNickname() + " " + ERR_NOTONCHANNEL(arg1);
	case 461:
		return " 461 " + this->_client->getNickname() + " " + ERR_NEEDMOREPARAMS(arg1);
	case 462:
		return " 462 " + this->_client->getNickname() + " " + ERR_ALREADYREGISTERED();
	case 464:
		return " 464 " + this->_client->getNickname() + " " + ERR_PASSWDMISMATCH();
	case 467:
		return " 467 " + this->_client->getNickname() + " " + ERR_KEYSET(arg1);
	case 472:
		return " 472 " + this->_client->getNickname() + " " + ERR_UNKNOWNMODE(arg1);
	case 482:
		return " 482 " + this->_client->getNickname() + " " + ERR_CHANOPRIVSNEEDED(arg1);
	case 501:
		return " 501 " + this->_client->getNickname() + " " + ERR_UMODEUNKNOWNFLAG();
	case 502:
		return " 502 " + this->_client->getNickname() + " " + ERR_USERSDONTMATCH();
	}
	return "UNKNOWN ERROR !";
};