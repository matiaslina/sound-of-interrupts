#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>

/* pulseaudio libs */
#include <pulse/simple.h>
#include <pulse/error.h>

#include "proc_parser.h"

#define BUFSIZE 1024

static int make_a_noise(uint32_t freq);
static int play_buffer(uint8_t *buf, uint32_t bufsize);

static int
play_buffer(uint8_t *buf, uint32_t bufsize)
{
    int result = -1;
    int error;
    pa_simple *pas = NULL;
    static const pa_sample_spec sample_spec = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 1
    };

    /* Create playback stream */
    if(!(pas = pa_simple_new(NULL, "play_sound", PA_STREAM_PLAYBACK,
                             NULL, "samples", &sample_spec, NULL, NULL,
                             &error)))
    {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n",
                pa_strerror(error));
        return result;
    }

    /* play it :) */
    if(pa_simple_write(pas, buf, (size_t) bufsize, &error) < 0)
    {
        fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n",
                pa_strerror(error));
        return result;
    }

    /* Make sure that every single sample was played */
    if(pa_simple_drain(pas, &error) < 0)
    {
        fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n",
                pa_strerror(error));
        return result;
    }

    result = 0;
    if(pas)
        pa_simple_free(pas);

    return result;
}

static int
make_a_noise(uint32_t freq)
{
    int sts = -1;
    uint8_t *buf = NULL;
    uint32_t bufsize, i, samples_to_play;
    float sample_rate;
    float played, playtime;
    float amplitude;

    sample_rate = 44100.0;
    playtime = 0.15;

    samples_to_play = (uint32_t)(playtime * sample_rate);

    bufsize = samples_to_play;
    buf = (uint8_t *)malloc(bufsize);
    if(buf)
    {
        for(i = 0; i < samples_to_play; ++i)
        {
            played = (float)i / (float)samples_to_play;
            amplitude = freq * (1.0 - played);
            buf[i] = (uint8_t)(amplitude * 30);
        }

        sts = play_buffer(buf, bufsize);
        free(buf);
    }

    return sts;
}

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
