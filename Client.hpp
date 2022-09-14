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
    void    receiveMessage() {
        char    buff[1024];
        int     bytes;
        bytes = recv(this->_sock, buff, 1024, 0);
        buff[bytes] = '\0';
        this->_buff += buff;
    };
    void    sendMessage() {
        if (this->_packets.size() > 0) {
            std::string packet = this->_packets[0];
            send(this->_sock, packet.c_str(), packet.size(), 0);
            this->_packets.erase(this->_packets.begin());
        }
    };
};

#endif