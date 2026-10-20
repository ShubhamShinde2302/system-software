
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t p1 = fork();

    if (p1 == -1) {
        perror("fork");
        return 1;
    }

    if (p1 == 0) {
        // Child 1: ls -l
        close(fd[0]);

        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(fd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    pid_t p2 = fork();

    if (p2 == -1) {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        waitpid(p1, NULL, 0);
        return 1;
    }

    if (p2 == 0) {
        // Child 2: wc
        close(fd[1]);

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(fd[0]);

        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_dup2_34.c -o question34dup2
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question34dup2
     49     434    3011
*/