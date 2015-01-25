#include <sys/select.h>

#include "eventloop.h"

EventLoop::EventLoop() :
    _run(true),
    _exitCode(0)
{

}

EventLoop::~EventLoop()
{

}

int EventLoop::exec()
{
    while (this->_run) {
        fd_set readFds, writeFds;
        std::map<int, EventObject*>::iterator it;
        int max_fd = 0;
        timeval timeout = {0,0};
        int result = 0;

        FD_ZERO(&readFds);
        for (it = this->_readFds.begin(); it != this->_readFds.end(); ++it) {
            int fd = it->first;
            if (fd > max_fd)
                max_fd = fd;
            FD_SET(fd, &readFds);
        }

        FD_ZERO(&writeFds);
        for (it = this->_writeFds.begin(); it != this->_writeFds.end(); ++it) {
            int fd = it->first;
            if (fd > max_fd)
                max_fd = fd;
            FD_SET(fd, &writeFds);
        }

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        result = select(max_fd + 1, &readFds, &writeFds, 0, &timeout);
        if (result > 0) {
            for (it = this->_readFds.begin(); it != this->_readFds.end(); ++it) {
                int fd = it->first;
                EventObject *obj = it->second;
                if (FD_ISSET(fd, &readFds)) {
                    obj->readyRead(fd);
                }
            }

            for (it = this->_writeFds.begin(); it != this->_writeFds.end(); ++it) {
                int fd = it->first;
                EventObject *obj = it->second;
                if (FD_ISSET(fd, &writeFds)) {
                    obj->readyWrite(fd);
                }
            }
        }
    }
}

void EventLoop::exit(int code)
{
    this->_exitCode = code;
    this->_run = false;
}

void EventLoop::transferObject(EventLoop *loop, EventObject *obj)
{
    std::map<int, EventObject*>::iterator it;

    it = this->_readFds.begin();
    while (it != this->_readFds.end()) {
        int fd = it->first;
        if (obj == it->second) {
            loop->_readFds[fd] = obj;
            this->_readFds.erase(it++);
        } else {
            ++it;
        }
    }

    it = this->_writeFds.begin();
    while (it != this->_writeFds.end()) {
        int fd = it->first;
        if (obj == it->second) {
            loop->_writeFds[fd] = obj;
            this->_writeFds.erase(it++);
        } else {
            ++it;
        }
    }
}

void EventLoop::registerRead(int fd, EventObject *obj)
{
    this->_readFds[fd] = obj;
}

void EventLoop::registerWrite(int fd, EventObject *obj)
{
    this->_writeFds[fd] = obj;
}

void EventLoop::unregister(int fd)
{
    this->_readFds.erase(fd);
    this->_writeFds.erase(fd);
}

