#include <QDebug>
#include <iostream>
#include "graphic_widget.h"

GraphWidget::GraphWidget(void)
{
    uint32_t i = 0;
    this->max = 0;
    for(i = 0; i < G_DIVISORS; ++i)
        this->divisors[i] = 0;
    this->setBackgroundRole(QPalette::Base);
    this->setAutoFillBackground(true);
    qDebug() << this->height();
}
void GraphWidget::set_max(void)
{
    uint32_t i;
    this->max = this->divisors[0];
    for(i = 0; i < G_DIVISORS; ++i)
        this->max = (this->max < this->divisors[i])? this->divisors[i]:this->max;
}

void GraphWidget::update_(uint32_t intr_sum)
{
    uint32_t i;
    /* Will ignore this */
    if (intr_sum > (1<<27))
        intr_sum = 0;

    for(i = 1; i < G_DIVISORS; ++i)
        this->divisors[i-1] = this->divisors[i];
    this->divisors[G_DIVISORS-1] = intr_sum;

    set_max();

    this->update();
}

void GraphWidget::paintEvent(QPaintEvent *)
{
    uint32_t i = 0;
    uint32_t line_width;
    uint32_t pre_x, pre_y;
    
    QPainter painter(this);
    line_width = this->width()/G_DIVISORS;
    pre_x = pre_y = 0;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    /* Better? should need some operations */
    painter.scale(1,0.1);


    /* drawLine(x1, y1, x2, y2) */
    for(i = 0; i < G_DIVISORS; ++i)
    {
        painter.drawLine(pre_x,
                         pre_y,
                         line_width*i,
                         this->divisors[i]);
        pre_x = line_width * i;
        pre_y = this->divisors[i];
    }
}
