#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int main()
{
    int policy;

    // Get current scheduling policy
    policy = sched_getscheduler(0);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: ");

    if (policy == SCHED_OTHER)
        printf("SCHED_OTHER\n");
    else if (policy == SCHED_FIFO)
        printf("SCHED_FIFO\n");
    else if (policy == SCHED_RR)
        printf("SCHED_RR\n");

    // Change policy to SCHED_FIFO
    struct sched_param param;
    param.sched_priority = 10;

    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Scheduling policy changed to SCHED_FIFO\n");

    // Get the new policy
    policy = sched_getscheduler(0);

    if (policy == SCHED_FIFO)
        printf("New scheduling policy: SCHED_FIFO\n");

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_29.c -o question_29
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_29
Current scheduling policy: SCHED_OTHER
sched_setscheduler: Operation not permitted

Note: SCHED_FIFO is a real-time policy, and Linux only allows a normal user
to switch a process into it if that user has the CAP_SYS_NICE capability or
a non-zero RLIMIT_RTPRIO (check with "ulimit -r"), which is 0 by default on
Ubuntu desktop installs. That is why sched_setscheduler() fails here with
EPERM and the program exits before printing "Scheduling policy changed...".

Running the same program as root (or via sudo) succeeds instead:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ sudo ./question_29
Current scheduling policy: SCHED_OTHER
Scheduling policy changed to SCHED_FIFO
New scheduling policy: SCHED_FIFO

==================================================== */
