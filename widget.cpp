#include <stdio.h>
#include "widget.h"

Widget::Widget(int id) :
    id(id)
{
    // Nothing to do
}

void Widget::slot(void)
{
    printf("Widget %d's slot invoked\n", this->id);
}

void Widget::onUpdated(void)
{
    this->Updated();
}
