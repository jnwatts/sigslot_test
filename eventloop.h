#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <map>
#include "eventobject.h"

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    int exec(void);
    void exit(int code = 0);

    void transferObject(EventLoop *loop, EventObject *obj);
    void registerRead(int fd, EventObject *obj);
    void registerWrite(int fd, EventObject *obj);
    void unregister(int fd);

private:
    bool _run;
    int _exitCode;
    std::map<int, EventObject *> _readFds;
    std::map<int, EventObject *> _writeFds;
};

#endif // EVENTLOOP_H
