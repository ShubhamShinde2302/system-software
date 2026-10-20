
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int p1[2], p2[2];

    // Create two pipes
    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("pipe");
        return 1;
    }

    // First process: ls -l
    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        dup2(p1[1], STDOUT_FILENO);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    // Second process: grep ^d
    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("grep", "grep", "^d", (char *)NULL);
        perror("execlp grep");
        _exit(1);
    }

    // Third process: wc
    pid_t pid3 = fork();

    if (pid3 == -1) {
        perror("fork");
        return 1;
    }

    if (pid3 == 0) {
        dup2(p2[0], STDIN_FILENO);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        _exit(1);
    }

    // Parent closes all pipe ends
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    // Wait for all child processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_35.c -o question35
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question35
      2      18     107
*/