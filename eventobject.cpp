#include "eventobject.h"

EventObject::EventObject(EventLoop *loop) :
    loop(loop)
{

}

EventObject::~EventObject()
{

}

void EventObject::setLoop(EventLoop *loop)
{
    if (this->loop) {
        this->loop->transferObject(loop, this);
    }
    this->loop = loop;
}

