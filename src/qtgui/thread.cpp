#include <unistd.h>
#include <stdlib.h>

#include "thread.h"

extern "C" {
    uint32_t *cpu_interrupts(void);
}

void ProcThread::finish(void)
{
    this->running = false;
}

void ProcThread::set_cpun(uint16_t count)
{
    this->cpun = count;
}

void ProcThread::run()
{
    this->interrupts_pre_ptr = NULL;
    this->interrupts_post_ptr = NULL;
    uint32_t *interr_diff = NULL;
    uint16_t i = 0;

    this->running = true;
    interr_diff =(uint32_t*) calloc(cpun, sizeof(uint32_t));

    while(this->running)
    {
        this->interrupts_post_ptr = cpu_interrupts();
        if(this->interrupts_pre_ptr)
            for(i = 0; i < this->cpun; ++i)
                interr_diff[i] = this->interrupts_post_ptr[i] - 
                                 this->interrupts_pre_ptr[i];

        emit send_interrupts(interr_diff);
        sleep(1);

        /* Now we should free this :) */
        if(this->interrupts_pre_ptr)
        {
            free(this->interrupts_pre_ptr);
            this->interrupts_pre_ptr = NULL;
        }

        /* And get the next pointer*/
        this->interrupts_pre_ptr = this->interrupts_post_ptr;
    }

    /* When we finish, free all */
    if(this->interrupts_post_ptr)
        free(this->interrupts_post_ptr);
    this->interrupts_pre_ptr = NULL;
    this->interrupts_post_ptr = NULL;
}
