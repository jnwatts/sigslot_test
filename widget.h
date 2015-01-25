#ifndef WIDGET_H__
#define WIDGET_H__

#include "eventobject.h"
#include "sigslot.h"
#include "server.h"
#include "simpleclient.h"

class Widget : public sigslot::has_slots<>, public EventObject
{
public:
    Widget(int _id, EventLoop *loop = 0);
    ~Widget(void);

    void NewClient(void);

private:
    Server _server;
    std::list<SimpleClient*> _clients;
    int _id;
};

#endif
