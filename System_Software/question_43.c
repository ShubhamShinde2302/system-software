
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a key
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create or access the message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Prepare the message
    msg.mtype = 1;

    printf("Enter a message: ");
    if (fgets(msg.mtext, sizeof(msg.mtext), stdin) == NULL) {
        fprintf(stderr, "Failed to read message\n");
        return 1;
    }

    msg.mtext[strcspn(msg.mtext, "\n")] = '\0';

    // Send the message
    if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent successfully!\n");
    printf("Message Queue Key: %d\n", (int)key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ cd System_Software
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question43
Enter a message: Shubham
Message sent successfully!
Message Queue Key: 1090862868
Message Queue ID: 0
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x41053f14 0          shubham    666        8            1           

*/