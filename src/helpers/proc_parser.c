#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc_parser.h"

#define PROC_FILE "/proc/interrupts"
/* Should be enough to read all the file */
#define BUFSIZE 4096

/* Check for the `ERR:` label in the proc file.
 * this should be our end of file. (need to check a better
 * way to handle this.) */
static int ERR_checker(char *ptr);

/* example of my /proc/interrupts
 * ==============================
 *
           CPU0       CPU1       CPU2       CPU3
  0:         29          0          0          0   IO-APIC-edge      timer
  1:      25839          0          0          0   IO-APIC-edge      i8042
  8:          1          0          0          0   IO-APIC-edge      rtc0
  9:       1382          0          0          0   IO-APIC-fasteoi   acpi
 12:    1141870          0          0          0   IO-APIC-edge      i8042
 16:     383743          0          0          0   IO-APIC-fasteoi   ehci_hcd:usb1, rtl_pci
 23:         80          0          0          0   IO-APIC-fasteoi   ehci_hcd:usb2
 40:       8233          0          0     173357   PCI-MSI-edge      ahci
 41:         66          0     284027          0   PCI-MSI-edge      i915
 42:         12          0          0          0   PCI-MSI-edge      mei_me
 43:          0          0          0          0   PCI-MSI-edge      p1p1
 44:        579          0          0          0   PCI-MSI-edge      snd_hda_intel
NMI:         41         35         35         45   Non-maskable interrupts
LOC:    1019275     956696     760092     857256   Local timer interrupts
SPU:          0          0          0          0   Spurious interrupts
PMI:         41         35         35         45   Performance monitoring interrupts
IWI:      31884      17910      19698      36354   IRQ work interrupts
RTR:          1          0          0          0   APIC ICR read retries
RES:      74948      79274      54116      29145   Rescheduling interrupts
CAL:        641        789        725        705   Function call interrupts
TLB:       9308      11141      12949      15414   TLB shootdowns
TRM:          0          0          0          0   Thermal event interrupts
THR:          0          0          0          0   Threshold APIC interrupts
MCE:          0          0          0          0   Machine check exceptions
MCP:         28         28         28         28   Machine check polls
ERR:          0
MIS:          0
*/

int
cpu_count(void)
{
    int result = -1;
    int fd = -1;
    char *buf = NULL;
    int finished = 0;
    int i;

    if((fd = open(PROC_FILE, O_RDONLY)) < 0)
    {
        fprintf(stderr, __FILE__": open() failed: %s\n",
                strerror(errno));
        return result;
    }

    buf = calloc(BUFSIZE, sizeof(char));
    result = 0;

    while(!finished)
    {
        if(read(fd, buf, BUFSIZE) < 0)
        {
            fprintf(stderr, __FILE__": open() failed: %s\n",
                    strerror(errno));
            return result;
        }

        for(i = 0; i < BUFSIZE; ++i)
        {
            if(buf[i] == 'C')
                result++;
            if(buf[i] == '0' && buf[i+1] == ':')
            {
                finished = 1;
                break;
            }
        }
    }

    close(fd);

    free(buf);
    return result;
}

static int
ERR_checker(char *ptr)
{
    return ((char)*(ptr-1) == 'R' &&
            (char)*(ptr-2) == 'R' &&
            (char)*(ptr-3) == 'E');
}

uint32_t *
cpu_interrupts(void)
{
    uint32_t *interrupts = NULL;
    char *buf = NULL;
    char number[32]; /* Don't think that this would be greater */
    int number_off;
    int buffer_index, interrupt_index = -1;
    int fd;
    int cpus = 0;

    /* Open the file. */
    if((fd = open(PROC_FILE, O_RDONLY)) < 0)
    {
        fprintf(stderr, __FILE__": open() failed: %s\n",
                strerror(errno));
        return interrupts;
    }

    /* Initialize the buffer */
    buf = calloc(BUFSIZE, sizeof(char));

    /* Read the file. if we can't, return null */
    if(read(fd, buf, BUFSIZE) < 0)
    {
        fprintf(stderr, __FILE__": open() failed: %s\n",
                strerror(errno));
        return interrupts;
    }

    /* Initialize the counters. */
    cpus = cpu_count();
    interrupts = calloc(cpus, sizeof(uint32_t));

    for(buffer_index = 0; buffer_index < BUFSIZE; buffer_index++)
    {
        if(buf[buffer_index] == ':')
        {
            if(ERR_checker(&(buf[buffer_index])))
                break;
            interrupt_index = 0;
            buffer_index++; /* move forward one step. */
        }
        if(interrupt_index < 0 || interrupt_index > (cpus-1))
            continue;

        if(buf[buffer_index] == ' ')
            continue;

        number_off = 0;
        while(buf[buffer_index] != ' ')
        {
            number[number_off] = buf[buffer_index];
            buffer_index++;
            if(buffer_index >= BUFSIZE)
                break;
            number_off++;
        }

        number[number_off] = '\0';

        interrupts[interrupt_index] += atoi(number);
        interrupt_index++;
    }
    close(fd);
    free(buf);

    return interrupts;
}
