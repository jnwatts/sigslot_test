#include <stdio.h>
#include "eventloop.h"
#include "server.h"
#include "widget.h"

int main()
{
    EventLoop eventLoop;
    Widget w(0, &eventLoop);

    return eventLoop.exec();
}
