#include <unistd.h>

#include "thread.h"

extern "C" {
    uint32_t *cpu_interrupts(void);
}

void ProcThread::finish(void)
{
    this->running = false;
}

void ProcThread::run()
{
    this->running = true;
    while(this->running)
    {
        interrupts_ptr = cpu_interrupts();
        emit send_interrupts(interrupts_ptr);
        sleep(1);

        /* Now we should free this :) */
        free(interrupts_ptr);
    }
}
