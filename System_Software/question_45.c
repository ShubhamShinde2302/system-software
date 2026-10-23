
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate the same key used to create the queue
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

    // Get current queue information
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("IPC_STAT");
        return 1;
    }

    printf("Old permissions: %03o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    // Change permissions to owner read/write only
    info.msg_perm.mode =
        (info.msg_perm.mode & ~0777) | 0600;

    // Apply the modified permissions
    if (msgctl(msgid, IPC_SET, &info) == -1) {
        perror("IPC_SET");
        return 1;
    }

    // Verify the new permissions
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("IPC_STAT");
        return 1;
    }

    printf("New permissions: %03o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    printf("Message queue permissions changed successfully.\n");

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_45.c -o question45
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question45 
Old permissions: 666
New permissions: 600
Message queue permissions changed successfully.

*/