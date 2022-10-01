/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/27 19:20:56 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMANDSRET_HPP
# define  COMMANDSRET_HPP

# include <iostream>
# include "Commands.hpp"


void	PASS(Commands* command);
void	NICK(Commands* command);
void	ISON(Commands* command);
void	INFO(Commands* command);
void	USER(Commands* command);
void	TIME(Commands* command);
void	PING(Commands* command);
void	PONG(Commands* command);
void	MOTD(Commands* command);
void	LUSERS(Commands* command);
void	MODE(Commands* command);
void	JOIN(Commands* command);
void	PRIVMSG(Commands* command);
void	PART(Commands* command);
void	TOPIC(Commands* command);

#endif