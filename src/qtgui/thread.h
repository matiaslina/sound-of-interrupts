#include <QtGui>
#include <stdint.h>

class ProcThread : public QThread
{
    Q_OBJECT

    public:
        void finish(void);

    signals:
        void send_interrupts(uint32_t *interrupts);

    private:
        void run();

        uint32_t *interrupts_ptr;
        bool running;
};
