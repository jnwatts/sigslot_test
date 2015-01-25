#ifndef SERVER_H__
#define SERVER_H__

#include <list>
#include <sys/socket.h>
#include "eventobject.h"
#include "sigslot.h"

class Server : public sigslot::has_slots<>, public EventObject
{
public:
    Server(EventLoop *loop = 0);
    ~Server();

    sigslot::signal0<> NewConnection;

    void readyRead(int fd);
    void readyWrite(int fd);

    bool listen(int port);
    int accept(struct sockaddr *addr = 0, socklen_t *addr_len = 0);

private:
    void registerFd(void);

    int _port;
    int _fd;
};

#endif
