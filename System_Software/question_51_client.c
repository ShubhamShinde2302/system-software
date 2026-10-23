
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

    // Supply the server's IP address as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <server-IP-address>\n", argv[0]);
        return 1;
    }

    // 1. Create a TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, argv[1],
                  &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address.\n");
        close(sock_fd);
        return 1;
    }

    // 3. Connect to the server
    if (connect(sock_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    // 4. Send a message
    const char *message = "Hello from the client machine!";

    if (send(sock_fd, message, strlen(message), 0) == -1) {
        perror("send");
        close(sock_fd);
        return 1;
    }

    // 5. Receive the server's reply
    ssize_t bytes = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Reply from server: %s\n", buffer);
    } else if (bytes == 0) {
        printf("Server closed the connection.\n");
    } else {
        perror("recv");
    }

    // 6. Close the socket
    close(sock_fd);

    return 0;
}

/*
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question51C 100.130.113.161
Connected to server.
Reply from server: Message received by server!
*/