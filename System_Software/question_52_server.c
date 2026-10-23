
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define PORT 8080

int main(void)
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[1024];

    // Prevent terminated child processes from becoming zombies
    signal(SIGCHLD, SIG_IGN);

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

    // 4. Listen for clients
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Fork-based server listening on port %d...\n", PORT);

    while (1) {
        client_len = sizeof(client_addr);

        // 5. Accept a client
        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &client_len);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // 6. Create a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            close(client_fd);
            continue;
        }

        if (pid == 0) {
            // Child handles this client
            close(server_fd);

            ssize_t n = recv(client_fd, buffer,
                             sizeof(buffer) - 1, 0);

            if (n > 0) {
                buffer[n] = '\0';
                printf("Child %ld received: %s\n",
                       (long)getpid(), buffer);

                const char *reply = "Handled by fork-based server";
                send(client_fd, reply, strlen(reply), 0);
            }

            close(client_fd);
            _exit(0);
        } else {
            // Parent continues accepting new clients
            close(client_fd);
        }
    }

    close(server_fd);
    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_52_server.c -o server52
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./server52
Fork-based server listening on port 8080...
Child 32144 received: Hello from client!
Child 32230 received: Hello from client!

*/