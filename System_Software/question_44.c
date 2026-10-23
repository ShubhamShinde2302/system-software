
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100];
};

int main(int argc, char *argv[]) {
    key_t key;
    int msgid;
    int flag;
    struct message msg;

    if (argc != 2) {
        printf("Usage: %s 0|1\n", argv[0]);
        printf("Use 0 for blocking, 1 for IPC_NOWAIT\n");
        return 1;
    }

    // Select the receiving flag
    if (argv[1][0] == '0' && argv[1][1] == '\0') {
        flag = 0;
    } else if (argv[1][0] == '1' && argv[1][1] == '\0') {
        flag = IPC_NOWAIT;
    } else {
        printf("Invalid flag. Use 0 or 1.\n");
        return 1;
    }

    // Generate the same key used by the sender
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Access the existing message queue
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    printf("Waiting to receive a message...\n");

    // Receive a message of any type
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 0, flag) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received message: %s\n", msg.mtext);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_44.c -o question44
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question44
Usage: ./question44 0|1
Use 0 for blocking, 1 for IPC_NOWAIT
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question44 0
Waiting to receive a message...
Received message: Shubham
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ 
*/