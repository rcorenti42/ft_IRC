#include "ConnectionManager.hpp"

ConnectionManager *ConnectionManager::_instance = 0;
ConnectionManager::ConnectionManager() {
	_epoll_fd = epoll_create1(0);
	if (_epoll_fd == -1) exit(-1);
}

ConnectionManager *ConnectionManager::getInstance() {
	if (!_instance) _instance = new ConnectionManager();
	return _instance;
}

ConnectionManager::~ConnectionManager() {
	close(_epoll_fd);
}

void ConnectionManager::setPort(int port) {_port = port;}
