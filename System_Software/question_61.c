#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("SIGSEGV caught! Signal number: %d\n", signum);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    printf("Raising SIGSEGV...\n");
    raise(SIGSEGV);

    printf("Program continues after handling SIGSEGV.\n");

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_61.c -o question61
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question61
Raising SIGSEGV...
SIGSEGV caught! Signal number: 11
Program continues after handling SIGSEGV.
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("\nSIGINT caught! Signal number: %d\n", signum);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to generate SIGINT.\n");

    while (1) {
        pause();
    }

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_61.c -o question61
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question61
Press Ctrl+C to generate SIGINT.
^C
SIGINT caught! Signal number: 2
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("SIGFPE caught! Signal number: %d\n", signum);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    printf("Raising SIGFPE...\n");
    raise(SIGFPE);

    printf("Program continues after handling SIGFPE.\n");

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_61.c -o question61
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question61
Raising SIGFPE...
SIGFPE caught! Signal number: 8
Program continues after handling SIGFPE.
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/