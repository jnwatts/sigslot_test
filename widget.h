#ifndef WIDGET_H__
#define WIDGET_H__

#include "sigslot.h"

class Widget : public sigslot::has_slots<>
{
public:
    Widget(int id);

    sigslot::signal0<> Updated;

    void slot(void);
    void onUpdated(void);

private:
    int id;
};

#endif
