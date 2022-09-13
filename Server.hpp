/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/12 20:22:43               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   Server.hpp                                                               */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <sstream>
# include <iostream>
# include <vector>
# include <map>
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>

class Server {
    int                     _sock;
    int                     _port;
    std::string             _password;
    std::vector<pollfd>     _fds;
    std::map<int, Client*>  _clients;
public:
    void    setPort(char* port) {
        std::stringstream   ss(port);
        if (!(ss >> this->_port)) {
            std::cerr << "Invalid port" << std::endl;
            exit(1);
        }
    };
    void    setPassword(char* password) {
        this->_password.assign(password);
    };
    void    init() {
        int         opt = 1;
        sockaddr_in addr;
        if (!(this->_sock = socket(AF_INET, SOCK_STREAM, 0))) {
            std::cerr << "Socket failed" << std::endl;
            exit(1);
        }
        if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            std::cerr << "Setsockopt failed" << std::endl;
            exit(1);
        }
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(this->_port);
        if (bind(this->_sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
            std::cerr << "Bind failed" << std::endl;
            exit(1);
        }
        if (listen(this->_sock, 10) < 0) {
            std::cerr << "Listen failed" << std::endl;
            exit(1);
        }
        if (fcntl(this->_sock, F_SETFL, O_NONBLOCK) < 0) {
            std::cerr << "Fcntl failed" << std::endl;
            exit(1);
        }
        this->_fds.push_back(pollfd());
        this->_fds.back().fd = this->_sock;
        this->_fds.back().events = POLLIN;
    };
    void    acceptClient() {
        int         client;
        sockaddr_in addr;
        socklen_t   len = sizeof(addr);
        if ((client = accept(this->_sock, (sockaddr*)&addr, &len)) < 0) {
            std::cerr << "Accept failed" << std::endl;
            exit(1);
        }
        this->_clients[client] = new Client(client, addr);
        this->_fds.push_back(pollfd());
        this->_fds.back().fd = client;
        this->_fds.back().events = POLLIN;
    };
    void    run() {
        if (poll(this->_fds.data(), this->_fds.size(), -1) < 0) {
            std::cerr << "Poll failed" << std::endl;
            exit(1);
        }
        if (this->_fds[0].revents == POLLIN)
            acceptClient();
    };
};

#endif