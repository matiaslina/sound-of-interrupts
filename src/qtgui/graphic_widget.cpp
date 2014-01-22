#include <QDebug>
#include <iostream>
#include "graphic_widget.h"

GraphWidget::GraphWidget(void)
{
    uint32_t i = 0;
    for(i = 0; i < G_DIVISORS; ++i)
        this->divisors[i] = 0;
}

void GraphWidget::update_(uint32_t intr_sum)
{
    uint32_t i;

    for(i = 1; i < G_DIVISORS; ++i)
    {
        this->divisors[i-1] = this->divisors[i];
        qDebug() << "divisor " << ":" <<this->divisors[i-1];
    }
    this->divisors[G_DIVISORS-1] = intr_sum;
    this->update();
}

void GraphWidget::paintEvent(QPaintEvent *)
{
    uint32_t i = 0;
    uint32_t width;
    uint32_t pre_x, pre_y;

    QPainter painter(this);
    width = this->width()/G_DIVISORS;
    pre_x = pre_y = 0;

    painter.setBackground(QBrush(Qt::white));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    /* drawLine(x1, y1, x2, y2) */
    for(i = 0; i < G_DIVISORS; ++i)
    {
        painter.drawLine(pre_x,
                         pre_y,
                         width*i,
                         this->divisors[i]);
        pre_x = width * i;
        pre_y = this->divisors[i];
    }
}
