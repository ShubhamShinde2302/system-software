#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process started.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID before kill: %d\n", getppid());

        sleep(2);

        // Send SIGKILL to the parent process
        printf("Child sending SIGKILL to parent...\n");
        kill(getppid(), SIGKILL);

        sleep(2);

        printf("Parent PID after parent termination: %d\n", getppid());
        printf("Child is now an orphan process.\n");
    } else {
        // Parent process
        printf("Parent process started.\n");
        printf("Parent PID: %d\n", getpid());

        while (1) {
            pause();
        }
    }

    return 0;
}

/*
Output (PIDs may differ):
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_63.c -o question63
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question63
Parent process started.
Parent PID: 4500
Child process started.
Child PID: 4501
Parent PID before kill: 4500
Child sending SIGKILL to parent...
Parent PID after parent termination: 1
Child is now an orphan process.
*/