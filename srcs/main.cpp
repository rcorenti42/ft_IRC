/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/09/23 03:53:12 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include "Server.hpp"
#include "CommandsRet.hpp"

// int		main()
// {
// 	time_t date;
// 	date = time(NULL);
// 	struct tm *readable = localtime(&date);
// 	std::cout << asctime(readable);
// }

int main(int argc, char** argv) {
    Server              server;
    if (argc != 3)
	{
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }
    server.setPort(argv[1]);
    server.setPassword(argv[2]);
    server.init();
    while (1)
        server.run();
    return 0;
}