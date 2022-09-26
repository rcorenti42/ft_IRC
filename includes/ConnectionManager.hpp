#pragma once
#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>

class ConnectionManager {
private:
	static ConnectionManager *_instance;

	int _epoll_fd;
	int _port;

	ConnectionManager();
public:
	static ConnectionManager *getInstance();
	~ConnectionManager();
	void setPort(int port);
};
