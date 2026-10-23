
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

int main() {
    int fd;
    char buffer[100];
    fd_set readfds;
    struct timeval timeout;

    // Create FIFO
    if (mkfifo("myfifo", 0666) == -1) {
        // FIFO may already exist
        if (access("myfifo", F_OK) == -1) {
            perror("mkfifo");
            return 1;
        }
    }

    // Open FIFO in read-only, non-blocking mode
    fd = open("myfifo", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Monitor FIFO for reading
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for data in FIFO for 10 seconds...\n");

    int result = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
    } 
    else if (result == 0) {
        printf("Timeout! No data available within 10 seconds.\n");
    } 
    else {
        ssize_t n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';
            printf("Data received: %s\n", buffer);
        } else if (n == 0) {
            printf("No data received; FIFO has no writer.\n");
        } else {
            perror("read");
        }
    }

    close(fd);
    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question39
Waiting for data in FIFO for 10 seconds...
Timeout! No data available within 10 seconds.
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question39
Waiting for data in FIFO for 10 seconds...
Data received: Hello from FIFO

*/