/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/10/22 14:24:21 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <sstream>
#include "Server.hpp"

using std::stringstream;

bool	validPort(char* port) {
	for (int i = 0; port[i]; i++)
		if (!isdigit(port[i]))
			return false;
	return true;
};

int main(int argc, char** argv) {
	Server	*server = Server::getInstance();
	int		port;
    if (argc != 3)
	{
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }
	stringstream ss(argv[1]);
	if (!(ss >> port) || !validPort(argv[1])) {
		std::cerr << "Invalid port" << std::endl;
		exit(1);
	}
	try {
    	server->init(port, argv[2]);
		server->run();
		delete server;
	}
	catch (ConnectionManager::ConnectException &e) {std::cerr << e.what() << std::endl;}
    return 0;
}
