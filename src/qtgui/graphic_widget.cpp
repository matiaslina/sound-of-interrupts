#include "graphic_widget.h"
/*
GraphWidget::GraphWidget(void)
{
}
*/
void GraphWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawArc(50, 30, 150, 150, 0, 16*360);
}
