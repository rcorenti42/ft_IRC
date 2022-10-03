/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:10:53 by lothieve          #+#    #+#             */
/*   Updated: 2022/09/29 11:21:20 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception>
#include <string>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

using std::string;

class ConnectionManager {
private:
	typedef struct epoll_event EpollEvent;

	static ConnectionManager *_instance;

	int			_epoll_fd;
	int			_port;
	int			_sock;


	ConnectionManager();
public:
	class ConnectException : std::exception {
		private:
			const string &_what;
		public:
			ConnectException(const string &what);
			const char *what() const throw();
	};

	static ConnectionManager *getInstance();
	~ConnectionManager();
	void setPort(int port);
	void addClient(int clientFd);
	int waitForEvent();
	int getMainSock() const;
	void init(int port);
};
