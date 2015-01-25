#ifndef SERVER_H__
#define SERVER_H__

#include <list>
#include "sigslot.h"

class Server : public sigslot::has_slots<>
{
public:
    Server();

    sigslot::signal0<> NewConnection;

    void idle(void);
    bool listen(int port);
    int accept(void);

private:

    int _port;
    list<int> _pendingClients;
};

#endif
