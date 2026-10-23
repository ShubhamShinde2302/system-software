
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

void *handle_client(void *arg)
{
    int client_fd = *(int *)arg;
    free(arg);

    char buffer[1024];

    // Receive a message from the client
    ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';

        printf("Thread %lu received: %s\n",
               (unsigned long)pthread_self(), buffer);

        const char *reply = "Handled by thread-based server";

        if (send(client_fd, reply, strlen(reply), 0) == -1)
            perror("send");
    }

    close(client_fd);
    return NULL;
}

int main(void)
{
    int server_fd;
    struct sockaddr_in server_addr;

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Thread-based server listening on port %d...\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // 5. Accept a client
        int client_fd = accept(server_fd,
                               (struct sockaddr *)&client_addr,
                               &client_len);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // Allocate memory for this client's socket descriptor
        int *arg = malloc(sizeof(int));
        if (arg == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }

        *arg = client_fd;

        // 6. Create a separate thread for the client
        pthread_t tid;

        if (pthread_create(&tid, NULL, handle_client, arg) != 0) {
            fprintf(stderr, "Failed to create thread\n");
            close(client_fd);
            free(arg);
            continue;
        }

        // Thread cleans up its resources when it finishes
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
