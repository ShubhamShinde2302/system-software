
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    if (argc != 2) {
        printf("Usage: %s <server-IP>\n", argv[0]);
        return 1;
    }

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, argv[1],
                  &server_addr.sin_addr) != 1) {
        printf("Invalid IP address\n");
        close(sock_fd);
        return 1;
    }

    if (connect(sock_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock_fd);
        return 1;
    }

    const char *message = "Hello from client!";

    if (send(sock_fd, message, strlen(message), 0) == -1) {
        perror("send");
        close(sock_fd);
        return 1;
    }

    ssize_t n = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Server reply: %s\n", buffer);
    } else if (n == -1) {
        perror("recv");
    }

    close(sock_fd);
    return 0;
}

/*
Output :
hubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_52_client.c -o client52
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./client52
Usage: ./client52 <server-IP>
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./client52 127.0.0.1
Server reply: Handled by fork-based server
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./client52 127.0.0.2
Server reply: Handled by fork-based server
*/