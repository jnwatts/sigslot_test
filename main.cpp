#include <stdio.h>
#include "widget.h"

int main()
{
    Widget w0(0);
    Widget w1(1);

    w0.Updated.connect(&w1, &Widget::slot);
    w0.Updated.connect(&w0, &Widget::slot);

    w0.onUpdated();
    printf("Returning\n");
    return 0;
}
