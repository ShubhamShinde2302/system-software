/*
   53. Interval Timer Programming: Write separate programs for each time domain to set an interval timer for 10 seconds and 10 microseconds. 
    a. Use ITIMER_REAL 
    b. Use ITIMER_VIRTUAL 
    c. Use ITIMER_PROF
*/

// Use ITIMER_REAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "ITIMER_REAL expired!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void)
{
    struct itimerval timer;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // One-shot timer: 10 seconds + 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Zero interval means it does not repeat
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_REAL started: waiting for 10 seconds and 10 microseconds...\n");
    fflush(stdout);

    while (1)
        pause();

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_53.c -o question53
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question53
ITIMER_REAL started: waiting for 10 seconds and 10 microseconds...
ITIMER_REAL expired!
*/

// use ITIMER_VIRTUAL

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "ITIMER_VIRTUAL expired!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGVTALRM, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_VIRTUAL started: consuming user CPU time...\n");
    fflush(stdout);

    // Keep the process executing in user mode
    volatile unsigned long long i = 0;
    while (1)
        i++;

    return 0;
}

/*
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question53
ITIMER_VIRTUAL started: consuming user CPU time...
ITIMER_VIRTUAL expired!
*/

// use ITIMER_PROF

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "ITIMER_PROF expired!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGPROF, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_PROF started: consuming CPU time...\n");
    fflush(stdout);

    // Consume user CPU time until the timer expires
    volatile unsigned long long i = 0;
    while (1)
        i++;

    return 0;
}
/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_53.c -o question53
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question53
ITIMER_PROF started: consuming CPU time...
ITIMER_PROF expired!
*/