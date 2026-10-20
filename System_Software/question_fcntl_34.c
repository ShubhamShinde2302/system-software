
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
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
        close(STDOUT_FILENO);

        if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1) {
            perror("fcntl");
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
        close(STDIN_FILENO);

        if (fcntl(fd[0], F_DUPFD, STDIN_FILENO) == -1) {
            perror("fcntl");
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

Output:
    shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_fcntl_34.c -o questionfcntl34
    shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./questionfcntl34   
    51     452    3143
*/