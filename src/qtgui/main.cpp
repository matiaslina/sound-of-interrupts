#include <QApplication>
#include "main_window.h"
#include "thread.h"

int
main(int argc, char *argv[])
{
    uint32_t interrupts[4];
    QApplication app(argc, argv);
    MainWindow mw;
    ProcThread pt;

    app.setApplicationName("Sound of Interrupts");

    QObject::connect((const QObject*) &pt, SIGNAL(send_interrupts(uint32_t *)),
                     (const QObject*) &mw, SLOT(update_interrupts(uint32_t*)),
                     Qt::QueuedConnection);
    pt.set_cpun(4);
    pt.start();
    mw.set_cpu_count(4);

    mw.update_interrupts(interrupts);
    mw.show();

    app.exec();
    pt.finish();
    pt.quit();
    pt.wait();
    return 0;
}
