#include <stdio.h>
#include "widget.h"

Widget::Widget(int id, EventLoop *loop) :
    EventObject(loop),
    _server(loop),
    _id(id)
{
    this->_server.NewConnection.connect(this, &Widget::NewClient);
    this->_server.listen(4321);
}

Widget::~Widget()
{
    std::list<SimpleClient*>::iterator it;
    for (it = this->_clients.begin(); it != this->_clients.end(); ++it) {
        delete *it;
    }
}

void Widget::NewClient()
{
    int fd = this->_server.accept();
    if (fd > 0) {
        SimpleClient *client = new SimpleClient(fd, this->loop);
        this->_clients.push_back(client);
    }
}
