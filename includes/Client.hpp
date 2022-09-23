/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 00:57:15 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <ctime>
# include <vector>
# include <algorithm>
# include <map>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

class Commands;
class Server;

enum e_state {
    CONNECTED,
    CHECKPASS,
    REGISTERED,
    NONE
};

class Client {
    e_state                     				_state;
    int                         				_sock;
    std::string                 				_nickname;
    std::string                 				_username;
	std::string									_realname;
    std::string                 				_buff;
    std::string                 				_userMode;
    std::string                 				_channel;
	std::string									_addr;
    std::vector<std::string>    				_packets;
	std::vector<Commands*>						_commands;
	std::map<std::string, int(*)(Commands*)>	_listCommands;
    time_t                      				_ping;
public:
    Client(int, sockaddr_in);
    ~Client();
    int     	getSocket() const;
    std::string getNickname() const;
    std::string getUsername() const;
	std::string	getAddr() const;
	e_state		getStats() const;
    void    	setNickname(std::string nickname);
    void    	setUsername(std::string username);
	void		setRealName(std::string realname);
	std::string	stateMsg();
    void    	packetsHandler();
    void    	receiveMessage(Server* serv);
    void    	writeMessage(std::string message);
    void    	sendMessage();
    void    	registerClient(Commands* commands);
	void		setState(e_state mode);
};

#endif