
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buffer[100];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    char message[] = "Hello from the pipe!";

    // Write data into the pipe
    if (write(fd[1], message, strlen(message) + 1) == -1) {
        perror("Write failed");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    printf("Data written into the pipe successfully.\n");

    // Read data from the pipe
    ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("Read failed");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    // Display received data
    printf("Data received from the pipe: %s\n", buffer);

    // Close both ends
    close(fd[0]);
    close(fd[1]);

    return 0;
}


// output :
// shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_31.c -o question31
// shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question31
// Data written into the pipe successfully.
// Data received from the pipe: Hello from the pipe!