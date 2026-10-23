
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main(void)
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    // 1. Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. Bind the socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for client connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting on port %d...\n", PORT);

    // 5. Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                       &client_len);
    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s\n",
           inet_ntoa(client_addr.sin_addr));

    // 6. Receive a message from the client
    ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Message from client: %s\n", buffer);

        // 7. Send a reply
        const char *reply = "Message received by server!";
        if (send(client_fd, reply, strlen(reply), 0) == -1)
            perror("send");
    } else if (bytes == 0) {
        printf("Client disconnected.\n");
    } else {
        perror("recv");
    }

    // 8. Close sockets
    close(client_fd);
    close(server_fd);

    return 0;
}
/*
Output :

shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_51_client.c -o question51C
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question51
Server waiting on port 8080...
Client connected: 100.130.113.161
Message from client: Hello from the client machine!

*/