
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

int main() {
    long max_files;
    int fd[2];
    long pipe_size;

    // Get maximum number of open files for the process
    max_files = sysconf(_SC_OPEN_MAX);

    printf("Maximum number of open files: %ld\n", max_files);

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Get pipe buffer size
    pipe_size = fcntl(fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1) {
        perror("fcntl");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    printf("Pipe buffer size: %ld bytes\n", pipe_size);

    // Close pipe file descriptors
    close(fd[0]);
    close(fd[1]);

    return 0;
}

/* 
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_40.c -o question40
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question40
Maximum number of open files: 524288
Pipe buffer size: 65536 bytes

*/