
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[100];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Create the child process
    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(fd[1]);  // Close write end

        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);

        if (n == -1) {
            perror("Read failed");
            close(fd[0]);
            return 1;
        }

        buffer[n] = '\0';

        printf("Child received: %s\n", buffer);

        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]);  // Close read end

        char message[] = "Hello child, this message is from parent!";

        printf("Parent is sending data to child.\n");

        if (write(fd[1], message, strlen(message)) == -1) {
            perror("Write failed");
            close(fd[1]);
            waitpid(pid, NULL, 0);
            return 1;
        }

        close(fd[1]);
        waitpid(pid, NULL, 0);
    }

    return 0;
}

/* 
Output:

shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_32.c -o question32
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question32
Parent is sending data to child.
Child received: Hello child, this message is from parent!

*/