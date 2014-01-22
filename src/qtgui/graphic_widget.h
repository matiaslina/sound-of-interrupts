#ifndef GRAPHIC_WIDGET_H
#define GRAPHIC_WIDGET_H

#include <QtGui>
#include <QWidget>
#include <stdint.h>
#define G_DIVISORS 64

class GraphWidget : public QWidget
{
    Q_OBJECT

    public:
        GraphWidget(void);
        void update_(uint32_t intr_sum);

    protected:
        void paintEvent(QPaintEvent *);

    private:
        uint32_t divisors[G_DIVISORS];
        uint32_t max;
        void set_max(void);

    signals:

    public slots:

};

#endif
