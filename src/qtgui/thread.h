#include <QtGui>
#include <stdint.h>

class ProcThread : public QThread
{
    Q_OBJECT

    public:
        void finish(void);
        void set_cpun(uint16_t count);

    signals:
        void send_interrupts(uint32_t *interrupts);

    private:
        void run();

        uint32_t *interrupts_pre_ptr;
        uint32_t *interrupts_post_ptr;
        uint32_t cpun;
        bool running;
};
