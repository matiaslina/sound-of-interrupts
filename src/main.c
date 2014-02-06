#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "helpers/proc_parser.h"
#include "helpers/pa_noiser.h"

int
main(void)
{
    uint32_t *interrupts_pre = NULL;
    uint32_t *interrupts_post = NULL;
    uint32_t sum = 0;
    int cpun = cpu_count();
    int j;

    if(!(interrupts_pre = cpu_interrupts()))
    {
        fprintf(stderr, "Cannot get the number of interrupts");
        return EXIT_FAILURE;
    }
    printf("%d\n",cpun);

    while(1)
    {
        sum = 0;
        interrupts_post = cpu_interrupts();
        for(j = 0; j < cpun; j++)
        {
            sum += interrupts_post[j] - interrupts_pre[j];
        }
        if(make_a_noise(sum) < 0)
            goto finish;
        free(interrupts_pre);
        interrupts_pre = interrupts_post;
    }

finish:
    if(interrupts_pre)
        free(interrupts_pre);

    if(interrupts_post)
        free(interrupts_post);


    return EXIT_SUCCESS;
}
