#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "simpleclient.h"

SimpleClient::SimpleClient(int fd, EventLoop *loop) :
    EventObject(loop),
    _fd(fd)
{
    if (this->loop)
        this->loop->registerRead(fd, this);
}

SimpleClient::~SimpleClient()
{
    if (this->loop)
        this->loop->unregister(this->_fd);
    if (this->_fd > 0)
        close(this->_fd);
}

void SimpleClient::readyRead(int fd)
{
    int result = 0;
    char *buf[4096];
    do {
        result = read(fd, buf, sizeof(buf));
        if (result > 0) {
            printf("From client: %.*s\n", result, buf);
        }
    } while (result > 0);
    if (result <= 0) {
        printf("%s:%d\n", __PRETTY_FUNCTION__, __LINE__);
        if (result < 0) {
            if (errno == EAGAIN)
                return;
            perror("SimpleClient::readyRead()");
        }
        if (this->loop)
            this->loop->unregister(fd);
        close(fd);
        this->Disconnected();
    }
}

void SimpleClient::readyWrite(int fd)
{

}

