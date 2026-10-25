
 /*
    59. Signal Handling: Write separate programs using the signal system call to catch the following signals: 
    a. SIGSEGV 
    b. SIGINT 
    c. SIGFPE 
    d. SIGALRM (using the alarm system call) 
    e. SIGALRM (using the setitimer system call) 
    f. SIGVTALRM (using the setitimer system call) 
    g. SIGPROF (using the setitimer system call)

*/

// a. SIGSEGV
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig)
{
    printf("SIGSEGV caught! Signal number: %d\n", sig);
    fflush(stdout);
    exit(0);
}

int main(void)
{
    signal(SIGSEGV, handler);

    printf("Raising SIGSEGV...\n");
    raise(SIGSEGV);

    return 0;
}


/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
Raising SIGSEGV...
SIGSEGV caught! Signal number: 11
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/


// b. SIGINT

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("\nSIGINT caught! Signal number: %d\n", sig);
    fflush(stdout);
}

int main(void)
{
    signal(SIGINT, handler);

    printf("Press Ctrl+C to generate SIGINT.\n");

    while (1)
        pause();

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
Waiting for SIGINT. Press Ctrl+C to send the signal.
^C
SIGINT caught! Signal number: 2
*/

// c. SIGFPE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig)
{
    printf("SIGFPE caught! Signal number: %d\n", sig);
    fflush(stdout);
    exit(0);
}

int main(void)
{
    signal(SIGFPE, handler);

    printf("Raising SIGFPE...\n");
    raise(SIGFPE);

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
Raising SIGFPE...
SIGFPE caught! Signal number: 8
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/


// d. SIGALRM (using the alarm system call)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGALRM caught! Timer expired.\n");
    fflush(stdout);
    exit(0);
}

int main(void)
{
    signal(SIGALRM, handler);

    printf("Alarm set for 5 seconds...\n");
    alarm(5);

    while (1)
        pause();

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
Alarm set for 5 seconds...
SIGALRM caught! Signal number: 14
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/

// e. SIGALRM (using the setitimer system call)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "SIGALRM caught using setitimer!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer;

    signal(SIGALRM, handler);

    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_REAL started for 5 seconds...\n");
    fflush(stdout);

    while (1)
        pause();

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
ITIMER_REAL timer set for 5 seconds...
SIGALRM caught using setitimer()
*/

// f. SIGVTALRM (using the setitimer system call)
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "SIGVTALRM caught! Virtual timer expired.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer;

    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_VIRTUAL started for 2 seconds of CPU time...\n");
    fflush(stdout);

    volatile unsigned long long i = 0;
    while (1)
        i++;

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
ITIMER_VIRTUAL timer set for 2 seconds of CPU time...
SIGVTALRM caught using setitimer()
*/

// g. SIGPROF (using the setitimer system call)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "SIGPROF caught! Profiling timer expired.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_PROF started for 2 seconds of CPU time...\n");
    fflush(stdout);

    volatile unsigned long long i = 0;
    while (1)
        i++;

    return 0;
}


/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_59.c -o question59
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question59
ITIMER_PROF timer set for 2 seconds of CPU time...
SIGPROF caught using setitimer()
*/