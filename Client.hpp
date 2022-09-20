/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/18 21:19:51 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <ctime>
# include <vector>
# include <algorithm>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "Server.hpp"
# include "Commands.hpp"

class Client {
    enum e_state {
        CONNECTED,
        PASS,
        REGISTERED,
        NONE
    };
    e_state                     _state;
    int                         _sock;
    std::string                 _nickname;
    std::string                 _username;
    std::string                 _host;
    std::string                 _buff;
    std::string                 _userMode;
    std::string                 _channel;
    std::vector<std::string>    _packets;
	std::vector<Commands*>		_commands;
    time_t                      _ping;
public:
    Client(int sock, sockaddr_in addr):_state(PASS),  _sock(sock), _ping(std::time(NULL)) {
        fcntl(sock, F_SETFL, O_NONBLOCK);
        this->_host = inet_ntoa(addr.sin_addr);
    };
    ~Client() {
        close(this->_sock);
    };
    int     getSocket() const {
        return this->_sock;
    };
    std::string getNickname() const {
        return this->_nickname;
    };
    std::string getUsername() const {
        return this->_username;
    };
    void    setNickname(std::string nickname) {
        this->_nickname = nickname;
    };
    void    setUsername(std::string username) {
        this->_username = username;
    };
    void    packetsHandler() {
    	std::vector<Commands*>	commands;
		if (this->_state != NONE) {
			for (std::vector<Commands*>::iterator it = this->_commands.begin(); it != this->_commands.end(); it++) {
				if (this->_state == PASS) {
					if ((*it)->getCommand() != "PASS")
						continue ;
				}
				else if (this->_state == REGISTERED)
					if ((*it)->getCommand() != "NICK" && (*it)->getCommand() != "USER")
						continue ;
				commands.push_back(*it);
			}
			for (std::vector<Commands*>::iterator it = commands.begin(); it != commands.end(); it++) {
				if (std::find(this->_commands.begin(), this->_commands.end(), *it) != this->_commands.end())
					this->_commands.erase(std::find(this->_commands.begin(), this->_commands.end(), *it));
			}
        }
    };
    void    receiveMessage(Server* serv) {
        char    	buff[5];
		std::string	msg;
        size_t  	bytes;
        size_t  	pos;
        bytes = recv(this->_sock, buff, 4, 0);
		buff[bytes] = '\0';
        if (bytes < 1) {
			if (bytes == 0)
				this->_state = NONE;
			return ;
		}
        this->_buff += buff;
		std::cout << buff << std::endl;
        while ((pos = this->_buff.find("\r\n")) != std::string::npos) {
        	msg = this->_buff.substr(0, pos);
			this->_buff.erase(0, pos + 2);
			if (!msg.size())
				continue;
			this->_commands.push_back(new Commands(this, serv, msg));
        }
        packetsHandler();
    };
    void    writeMessage(std::string message) {
        // TODO
        std::cout << "Write message called" << std::endl;
        (void)message;
        return ;
    };
    void    sendMessage() {
        std::string packet;
        if (this->_packets.size()) {
            for (std::vector<std::string>::iterator it = this->_packets.begin(); it != this->_packets.end(); it++)
                packet += *it + "\r\n";
            this->_packets.clear();
            if (packet.size())
                send(this->_sock, packet.c_str(), packet.size(), 0);
        }
    };
    void    registerClient(Commands* commands) {
        // TODO
        std::cout << "registerClient called" << std::endl;
        (void)commands;
        return ;
    };
};

#endif