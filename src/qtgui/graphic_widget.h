#ifndef GRAPHIC_WIDGET_H
#define GRAPHIC_WIDGET_H

#include <QtGui>
#include <QWidget>

class GraphWidget : public QWidget
{
    Q_OBJECT

    public:
        //GraphWidget(void);

    protected:
        void paintEvent(QPaintEvent *);

    signals:

    public slots:

};

#endif
