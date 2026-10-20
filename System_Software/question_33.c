
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p2c[2], c2p[2];
    pid_t pid;
    char buffer[100];

    // Create two pipes
    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(p2c[1]);  // Child does not write to pipe 1
        close(c2p[0]);  // Child does not read from pipe 2

        // Receive message from parent
        ssize_t n = read(p2c[0], buffer, sizeof(buffer) - 1);

        if (n <= 0) {
            perror("Child read failed");
            close(p2c[0]);
            close(c2p[1]);
            return 1;
        }

        buffer[n] = '\0';
        printf("Child received: %s\n", buffer);

        // Send reply to parent
        char reply[] = "Hello parent, message received!";

        if (write(c2p[1], reply, strlen(reply) + 1) == -1) {
            perror("Child write failed");
            close(p2c[0]);
            close(c2p[1]);
            return 1;
        }

        close(p2c[0]);
        close(c2p[1]);
    }
    else {
        // Parent process
        close(p2c[0]);  // Parent does not read from pipe 1
        close(c2p[1]);  // Parent does not write to pipe 2

        // Send message to child
        char message[] = "Hello child, are you ready?";

        if (write(p2c[1], message, strlen(message) + 1) == -1) {
            perror("Parent write failed");
            close(p2c[1]);
            close(c2p[0]);
            waitpid(pid, NULL, 0);
            return 1;
        }

        close(p2c[1]);

        // Receive reply from child
        ssize_t n = read(c2p[0], buffer, sizeof(buffer) - 1);

        if (n <= 0) {
            perror("Parent read failed");
            close(c2p[0]);
            waitpid(pid, NULL, 0);
            return 1;
        }

        buffer[n] = '\0';
        printf("Parent received: %s\n", buffer);

        close(c2p[0]);
        waitpid(pid, NULL, 0);
    }

    return 0;
}

/*
Output:

shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_33.c -o question33
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question33
Parent is sending data to child.
Child received: Hello child, are you ready?
Parent received: Hello parent, message received!

*/