#ifndef SIMPLECLIENT_H
#define SIMPLECLIENT_H

#include "sigslot.h"
#include "eventobject.h"

class SimpleClient : public sigslot::has_slots<>, public EventObject
{
public:
    SimpleClient(int fd, EventLoop *loop = 0);
    ~SimpleClient();

    sigslot::signal0<> Disconnected;

    virtual void readyRead(int fd);
    virtual void readyWrite(int fd);

private:
    int _fd;
};

#endif // SIMPLECLIENT_H
