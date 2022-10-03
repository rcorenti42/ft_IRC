/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/30 14:27:56 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include "Commands.hpp"
#include "CommandManager.hpp"
#include "time.h"
#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <sstream>

class Commands;


void	PASS(Commands* command);
void	NICK(Commands* command);
void	INFO(Commands* command);
void	USER(Commands* command);
void	TIME(Commands* command);
void	MOTD(Commands* command);
void	LUSERS(Commands* command);
void	MODE(Commands* command);

