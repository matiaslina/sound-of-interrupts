#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <QLabel>
#include <stdint.h>
#include <stdio.h>

#include "graphic_widget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
        QLabel *cpu_interrupts_label;
        GraphWidget *graph;
    public:
        MainWindow(void);
        void set_cpu_count(uint32_t cpun);

        QLabel *get_cpu_interrupts_label(void);

    public slots:
        void update_interrupts(uint32_t *interrupts);

    protected:
        void close_event(QCloseEvent *event);

    private:
        uint32_t cpu_count;

};

#endif
