/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/15 08:34:31               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   Commands.hpp                                                             */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Client.hpp"
# include "Server.hpp"
# include <iostream>

class Client;
class Server;

class Commands {
	Client*						_client;
	Server*						_server;
	std::string					_command;
	std::vector<std::string>	_args;
public:
	Commands(Client *client, Server *server, std::string arg): _client(client), _server(server) {
	};
	std::string					getCommand() const {
		return this->_command;
	};
};

#endif