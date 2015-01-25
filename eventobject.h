#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include <list>

class EventLoop;

class EventObject
{
public:
    EventObject(EventLoop *loop = 0);
    ~EventObject();

    virtual void setLoop(EventLoop *loop);
    virtual void readyRead(int fd) { }
    virtual void readyWrite(int fd) { }

protected:
    EventLoop *loop;
};

#include "eventloop.h"

#endif // EVENTOBJECT_H
