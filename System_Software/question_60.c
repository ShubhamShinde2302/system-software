#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Ignore SIGINT
    signal(SIGINT, SIG_IGN);

    printf("SIGINT is ignored. Press Ctrl+C; it will be ignored.\n");
    sleep(5);

    // Reset SIGINT to its default action
    signal(SIGINT, SIG_DFL);

    printf("SIGINT reset to default. Press Ctrl+C again.\n");

    while (1) {
        pause();
    }

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_60.c -o question60
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question60
SIGINT is ignored. Press Ctrl+C; it will be ignored.
SIGINT reset to default. Press Ctrl+C again.
^C
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$
*/