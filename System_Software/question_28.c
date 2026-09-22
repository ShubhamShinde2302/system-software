#include <stdio.h>
#include <sched.h>

int main()
{
    int min_priority, max_priority;

    min_priority = sched_get_priority_min(SCHED_FIFO);
    max_priority = sched_get_priority_max(SCHED_FIFO);

    printf("Minimum real-time priority: %d\n", min_priority);
    printf("Maximum real-time priority: %d\n", max_priority);

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_28.c -o question_28
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_28
Minimum real-time priority: 1
Maximum real-time priority: 99

Note: these two numbers are fixed by the Linux kernel for the SCHED_FIFO
policy and do not depend on the machine, the user, or how many times the
program is run - they will always print 1 and 99.

==================================================== */
