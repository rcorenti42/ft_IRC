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
void	INFO(Commands* command);
void	USER(Commands* command);
void	TIME(Commands* command);
void	MOTD(Commands* command);
void	LUSERS(Commands* command);
void	MODE(Commands* command);


#endif