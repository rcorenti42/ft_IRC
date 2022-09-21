/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/21 08:18:54 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"
#include "Server.hpp"
#include "Commands.hpp"

int PASS(Commands* command);

Client::Client(int sock):_state(CHECKPASS), _sock(sock), _userMode("w"), _ping(std::time(NULL)) {
	this->_listCommands["PASS"] = PASS;
};
Client::~Client() {
    close(this->_sock);
};
int     Client::getSocket() const {
    return this->_sock;
};
std::string Client::getNickname() const {
    return this->_nickname;
};
std::string Client::getUsername() const {
    return this->_username;
};
e_state		Client::getStats() const {
	return this->_state;
};
void    Client::setNickname(std::string nickname) {
    this->_nickname = nickname;
};
void    Client::setUsername(std::string username) {
    this->_username = username;
};

void		Client::setState(e_state mode) {
	this->_state = mode;
}

void    Client::packetsHandler() {
	std::vector<Commands*>	commands;
	e_state					state = this->_state;
	if (this->_state != NONE) {
		for (std::vector<Commands*>::iterator it = this->_commands.begin(); it != this->_commands.end(); it++) {
			if (this->_state == CHECKPASS) {
				if ((*it)->getCommand() != "PASS")
					continue ;
			}
			else if (this->_state == REGISTERED)
				if ((*it)->getCommand() != "NICK" && (*it)->getCommand() != "USER")
					continue ;
			if (this->_listCommands.count((*it)->getCommand()))
				this->_listCommands[(*it)->getCommand()](*it);
			commands.push_back(*it);
		}
		for (std::vector<Commands*>::iterator it = commands.begin(); it != commands.end(); it++) {
			if (std::find(this->_commands.begin(), this->_commands.end(), *it) != this->_commands.end()) {
				this->_commands.erase(std::find(this->_commands.begin(), this->_commands.end(), *it));
				delete *it;
			}
		}
		if (this->_state == REGISTERED && this->_nickname.size())
			this->_state = CONNECTED;
		if (this->_state != state) {
			if (this->_state == CONNECTED)
				registerClient(*this->_commands.begin());
			packetsHandler();
		}
    }
};
void    Client::receiveMessage(Server* serv) {
    char    	buff[1025];
	std::string	msg;
    size_t  	bytes;
    size_t  	pos;
    bytes = recv(this->_sock, buff, 1024, 0);
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
void    Client::writeMessage(std::string message) {
	this->_packets.push_back(message);
};
void    Client::sendMessage() {
    std::string packet;
    if (this->_packets.size()) {
        for (std::vector<std::string>::iterator it = this->_packets.begin(); it != this->_packets.end(); it++)
            packet += *it + "\r\n";
        this->_packets.clear();
        if (packet.size())
            send(this->_sock, packet.c_str(), packet.size(), 0);
    }
};
void    Client::registerClient(Commands* commands) {
    // TODO
    std::cout << "registerClient called" << std::endl;
    (void)commands;
    return ;
};