#include <assert.h>
#include "main_window.h"

MainWindow::MainWindow(void)
{
    cpu_count = 0;

    QVBoxLayout *layout = new QVBoxLayout;
    
    /* Set the label */
    cpu_interrupts_label = new QLabel;
    cpu_interrupts_label->setText(QString("Retriving data from the cpus"));
    
    /* Set the graph */
    this->graph = new GraphWidget;
    this->graph->show();


    layout->addWidget(this->graph);
    layout->addWidget(cpu_interrupts_label);

    setLayout(layout);
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
