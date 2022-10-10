/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/10 11:05:24 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "CommandManager.hpp"
#include "Server.hpp"

class Server;
class CommandManager;
struct Context;

enum e_state {
    CONNECTED,
    CHECKPASS,
    REGISTERED,
    NONE
};

typedef void (*t_command)(Context &, std::string *);

class Client {
    e_state                     				_state;
    int                         				_sock;
    std::string                 				_nickname;
    std::string                 				_username;
	std::string									_realname;
    std::string                 				_buff;
    std::string                 				_mode;
    std::string                 				_channel;
	std::string									_addr;
	std::string									_quitMessage;
    std::vector<std::string>    				_packets;
	std::map<std::string, t_command>			_listCommands;
    time_t                      				_ping;
	CommandManager								*_cmdmgr;
public:
    Client(int, sockaddr_in);
    ~Client();
    int     	getSocket() const;
    std::string getNickname() const;
    std::string getUsername() const;
	std::string	getRealname() const;
	std::string	getMode() const;
	std::string	getAddr() const;
	std::string	getQuitMessage() const;
	e_state		getStats() const;
    void    	setNickname(std::string nickname);
    void    	setUsername(std::string username);
	void		setRealName(std::string realname);
	void		setQuitMessage(std::string message);
	void		setMode(std::string mode);
	void		setPing(time_t);
	std::string	stateMsg();
    void    	packetsHandler();
    void    	receiveMessage();
	void    	writePrefixMsg(int code, Client &client, std::string message);
	void    	writePrefixMsg(int code, std::string message);
	void		writePrefixMsg(Client& client, std::string message);
	void		writePrefixMsg(std::string message);
    void    	writeMessage(std::string message);
    void    	sendMessage();
    void    	registerClient();
	void		setState(e_state mode);
};
