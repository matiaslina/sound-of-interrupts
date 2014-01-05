#include <assert.h>
#include "main_window.h"

MainWindow::MainWindow(void)
{
    cpu_count = 0;
    cpu_interrupts_label = new QLabel(this);
    cpu_interrupts_label->setText(QString("Retriving data from the cpus"));
    setCentralWidget(cpu_interrupts_label);
}

void MainWindow::update_interrupts(uint32_t *interrupts)
{
    char buf[1024] = "";
    char aux[32] = "";
    unsigned int i;
    assert(this->cpu_count > 0);

    buf[1023] = '\0';
    for(i = 0; i < this->cpu_count; i++)
    {
        sprintf(aux, "CPU%d: %d\n", i, interrupts[i]);
        strncat(buf, aux, strlen(aux));
    }

    this->cpu_interrupts_label->setText(QString((const char *) buf));
}

QLabel *MainWindow::get_cpu_interrupts_label(void)
{
    return this->cpu_interrupts_label;
}

void MainWindow::set_cpu_count(uint32_t cpun)
{
    cpu_count = cpun;
}

void MainWindow::close_event(QCloseEvent *event)
{
    event->accept();
}
