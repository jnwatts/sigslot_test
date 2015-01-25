#include <stdio.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>

#include "server.h"


Server::Server(EventLoop *loop) :
    EventObject(loop),
    _port(0),
    _fd(0)
{
    // Nothing to do
}

Server::~Server()
{
    if (this->loop)
        this->loop->unregister(this->_fd);
}

void Server::readyRead(int fd)
{
    this->NewConnection();
}

void Server::readyWrite(int fd)
{

}

bool Server::listen(int port)
{
    int fd = 0;
    int val = 0;
    struct sockaddr_in addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        goto err;
    }

    val = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        perror("SO_REUSEADDR");
        goto err;
    }

    val = 1;
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
        perror("O_NONBLOCK");
        goto err;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        goto err;
    }

    if (::listen(fd, 1) < 0) {
        perror("listen");
        goto err;
    }

    this->_fd = fd;
    this->registerFd();
    return true;

err:
    if (fd > 0)
        close(fd);
    return false;
}

int Server::accept(struct sockaddr *addr, socklen_t *addr_len)
{
    return ::accept(this->_fd, addr, addr_len);
}

void Server::registerFd()
{
    if (this->loop) {
        this->loop->registerRead(this->_fd, this);
    }
}
