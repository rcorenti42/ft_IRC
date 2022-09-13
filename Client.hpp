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
# include <netinet/in.h>

class Client {
    int         _sock;
    std::string _nickname;
    std::string _username;
public:
    Client(int sock, sockaddr_in addr): _sock(sock) {
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
};

#endif