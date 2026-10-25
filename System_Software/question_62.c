#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    // Ignore SIGINT
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is ignored. Press Ctrl+C within 5 seconds.\n");
    sleep(5);

    // Reset SIGINT to its default action
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT reset to default. Press Ctrl+C again.\n");

    while (1) {
        pause();
    }

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_62.c -o question62
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question62
SIGINT is ignored. Press Ctrl+C within 5 seconds.
SIGINT reset to default. Press Ctrl+C again.
^C
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/