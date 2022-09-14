/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/13 04:04:43               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   Client.hpp                                                               */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

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
    std::vector<std::string>    _packets;
public:
    Client(int sock, sockaddr_in addr): _sock(sock) {
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
        e_state state = this->_state;
        if (state != NONE) {
            for (std::vector<std::string>::iterator it = this->_packets.begin(); it != this->_packets.end(); it++) {
                std::cout << "Packet: " << *it << std::endl;
                if (state == CONNECTED) {
                    if (*it == "PASS") {
                        this->_state = PASS;
                        state = PASS;
                    }
                    else if (*it == "NICK") {
                        this->_state = REGISTERED;
                        state = REGISTERED;
                    }
                    else {
                        this->_state = NONE;
                        state = NONE;
                    }
                }
                else if (state == PASS) {
                    if (*it == "NICK") {
                        this->_state = REGISTERED;
                        state = REGISTERED;
                    }
                    else {
                        this->_state = NONE;
                        state = NONE;
                    }
                }
                else if (state == REGISTERED) {
                    if (*it == "NICK") {
                        this->_state = REGISTERED;
                        state = REGISTERED;
                    }
                    else {
                        this->_state = NONE;
                        state = NONE;
                    }
                }
            }
            packetsHandler();
        }
    };
    void    receiveMessage() {
        char    buff[1024];
        size_t  bytes;
        size_t  pos;
        bytes = recv(this->_sock, buff, 1024, 0);
        buff[bytes] = '\0';
        this->_buff += buff;
        while ((pos = this->_buff.find("\r\n")) != std::string::npos) {
            this->_packets.push_back(this->_buff.substr(0, pos));
            this->_buff.erase(0, pos + 2);
        }
        packetsHandler();
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
};

#endif