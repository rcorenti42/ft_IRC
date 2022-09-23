/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsRet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 04:24:34 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMANDSRET_HPP
# define  COMMANDSRET_HPP

# include <iostream>
# include "Commands.hpp"


int	PASS(Commands* command);
int	NICK(Commands *command);
int	USER(Commands *command);
int	TIME(Commands *command);

std::string	RPL_WELCOME(std::string, std::string, std::string);

std::string	RPL_YOURHOST();

std::string	RPL_CREATED();

std::string	RPL_MYINFO();

#endif