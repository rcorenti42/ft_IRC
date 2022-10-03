/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsReply.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/03 01:24:12 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMANDSREPLY_HPP
# define COMMANDSREPLY_HPP

# include <iostream>

std::string	RPL_WELCOME(std::string, std::string, std::string);

std::string	RPL_YOURHOST();

std::string	RPL_CREATED();

std::string	RPL_MYINFO();

std::string	RPL_UMODEIS(std::string);

std::string	RPL_LUSERCLIENT(std::string, std::string);

std::string	RPL_LUSEROP(std::string);

std::string	RPL_LUSERUNKNOWN(std::string);

std::string	RPL_LUSERCHANNELS(std::string);

std::string	RPL_LUSERME(std::string);

std::string	RPL_CHANNELMODEIS(std::string, std::string);

std::string	RPL_NOTOPIC(std::string);

std::string	RPL_TOPIC(std::string, std::string);

std::string	RPL_BANLIST(std::string, std::string);

std::string	RPL_ENDOFBANLIST(std::string);

std::string	RPL_TIME(std::string);

std::string RPL_INFO(std::string);

std::string RPL_ENDOFINFO();

std::string	ERR_NOSUCHNICK(std::string);

std::string	ERR_NOSUCHCHANNEL(std::string);

std::string	ERR_NOORIGIN();

std::string	ERR_NORECIPIENT(std::string);

std::string	ERR_NOTEXTTOSEND();

std::string	ERR_NONICKNAMEGIVEN();

std::string	ERR_NICKNAMEINUSE(std::string);

std::string	ERR_NOTONCHANNEL(std::string);

std::string	ERR_NEEDMOREPARAMS(std::string);

std::string	ERR_ALREADYREGISTERED();

std::string	ERR_PASSWDMISMATCH();

std::string	ERR_KEYSET(std::string);

std::string	ERR_UNKNOWNMODE(std::string);

std::string	ERR_BADCHANMASK(std::string);

std::string	ERR_CHANOPRIVSNEEDED(std::string);

std::string	ERR_NOOPERHOST();

std::string	ERR_UMODEUNKNOWNFLAG();

std::string	ERR_USERSDONTMATCH();

#endif