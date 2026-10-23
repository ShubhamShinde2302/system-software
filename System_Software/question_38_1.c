
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char msg[100];
    int fd1, fd2;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    // Send message to Program 2
    fd1 = open("fifo1", O_WRONLY);

    printf("Program 1: Enter message: ");
    fgets(msg, sizeof(msg), stdin);
    write(fd1, msg, strlen(msg) + 1);
    close(fd1);

    // Receive reply from Program 2
    fd2 = open("fifo2", O_RDONLY);
    read(fd2, msg, sizeof(msg));
    printf("Program 1 received: %s", msg);
    close(fd2);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question38_1
Program 1: Enter message: shubham shinde
Program 1 received: Hello Shubham
*/