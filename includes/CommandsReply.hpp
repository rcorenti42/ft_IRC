/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/23 23:56:41               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   CommandsReply.hpp                                                        */
/* ************************************************************************** */

#ifndef COMMANDSREPLY_HPP
# define COMMANDSREPLY_HPP

# include <iostream>

std::string	RPL_WELCOME(std::string, std::string, std::string);

std::string	RPL_YOURHOST();

std::string	RPL_CREATED();

std::string	RPL_MYINFO();

std::string	RPL_LUSERCLIENT(std::string, std::string);

std::string	RPL_LUSEROP(std::string);

std::string	RPL_LUSERUNKNOWN(std::string);

std::string	RPL_LUSERCHANNELS(std::string);

std::string	RPL_LUSERME(std::string);

#endif