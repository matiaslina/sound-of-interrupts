#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <QLabel>
#include <stdint.h>
#include <stdio.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT
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
        QLabel *cpu_interrupts_label;
};

#endif
