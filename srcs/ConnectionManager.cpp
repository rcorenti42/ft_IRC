/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:10:51 by lothieve          #+#    #+#             */
/*   Updated: 2022/10/21 11:10:24 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionManager.hpp"

ConnectionManager *ConnectionManager::_instance = 0;

void ConnectionManager::init(int port) {
	sockaddr_in addr;
	int         opt = 1;

	_port = port;
	_epoll_fd = epoll_create1(0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(_port);
	if (_epoll_fd == -1) throw ConnectException("Failed to create epoll instance");
	if (!(_sock = socket(AF_INET, SOCK_STREAM, 0))) throw ConnectException("Socket failed");
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) throw ConnectException("Setsockopt failed");
	if (bind(_sock, (sockaddr*)&addr, sizeof(addr)) < 0) throw ConnectException("Bind failed");
	if (listen(_sock, 10) < 0) throw ConnectException("Listen failed");
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) < 0) throw ConnectException("Fcntl failed");
	addClient(_sock);
}

ConnectionManager *ConnectionManager::getInstance() {
	if (!_instance) _instance = new ConnectionManager();
	return _instance;
}

void ConnectionManager::setPort(int port) {_port = port;}
void ConnectionManager::addClient(int ClientFd) {
	EpollEvent ev;

	ev.events = EPOLLIN;
	ev.data.ptr = 0;
	ev.data.fd = ClientFd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, ClientFd, &ev) == -1) throw ConnectException("Client add failed");
}

int ConnectionManager::waitForEvent() {
	EpollEvent ev;
	int ret;

	ret = epoll_wait(_epoll_fd, &ev, 1, -1);
	if (ret < 0) throw ConnectException("Epoll wait failed");
	return ev.data.fd;
}

string		ConnectionManager::receivePacket(int socket) {
	std::ostringstream	ss;
	char				buf[1024];
	ssize_t				ret;

	do
	{
		bzero(buf, 1024);
		ret = recv(socket, buf, 1023, 0);
		ss << buf;
	} while (ret == 1024);
	if (ret == -1) throw ConnectException("Failed to receive packet");
	return ss.str();
}

int ConnectionManager::getMainSock() const {return _sock;}
ConnectionManager::ConnectionManager() {}
ConnectionManager::~ConnectionManager() {close(_epoll_fd);}
ConnectionManager::ConnectException::	ConnectException(const string &what) : _what(what) {}
const char *ConnectionManager::ConnectException::what() const throw() {(void)_what; return "Connection failed";}
