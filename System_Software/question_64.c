#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Program 1 started.\n");
    printf("PID of Program 1: %d\n", getpid());
    printf("Waiting for SIGSTOP signal...\n");

    while (1) {
        pause();
    }

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_64.c -o question64
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question64
Program 1 started.
PID of Program 1: 5200
Waiting for SIGSTOP signal...
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    if (kill(pid, SIGSTOP) == -1) {
        perror("kill failed");
        return 1;
    }

    printf("SIGSTOP sent to process %d successfully.\n", pid);

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_73.c -o question73
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question73 5200
SIGSTOP sent to process 5200 successfully.
*/