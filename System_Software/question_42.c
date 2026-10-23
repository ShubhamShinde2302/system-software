
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate a key
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Access or create the message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Get message queue information
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Message Queue ID: %d\n", msgid);
    printf("Access Permissions: %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    printf("UID: %u\n", (unsigned int)info.msg_perm.uid);
    printf("GID: %u\n", (unsigned int)info.msg_perm.gid);

    printf("Last Message Sent: %s",
           ctime(&info.msg_stime));
    printf("Last Message Received: %s",
           ctime(&info.msg_rtime));
    printf("Last Change in Queue: %s",
           ctime(&info.msg_ctime));

    printf("Current Queue Size: %lu bytes\n",
           (unsigned long)info.msg_cbytes);
    printf("Number of Messages: %lu\n",
           (unsigned long)info.msg_qnum);
    printf("Maximum Bytes Allowed: %lu bytes\n",
           (unsigned long)info.msg_qbytes);

    printf("PID of Last msgsnd: %d\n", info.msg_lspid);
    printf("PID of Last msgrcv: %d\n", info.msg_lrpid);

    return 0;
}

/* 
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_42.c -o question42
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question42
Message Queue ID: 0
Access Permissions: 666
UID: 1000
GID: 1000
Last Message Sent: Thu Jan  1 05:30:00 1970
Last Message Received: Thu Jan  1 05:30:00 1970
Last Change in Queue: Sat Oct 24 01:13:34 2026
Current Queue Size: 0 bytes
Number of Messages: 0
Maximum Bytes Allowed: 16384 bytes
PID of Last msgsnd: 0
PID of Last msgrcv: 0

*/