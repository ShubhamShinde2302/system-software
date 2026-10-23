
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key;
    int semid;

    // Generate a key
    key = ftok(".", 'B');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create one semaphore
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    // Initialize semaphore to 1
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    printf("Binary semaphore created successfully.\n");
    printf("Semaphore ID: %d\n", semid);
    printf("Initial value: %d\n", semctl(semid, 0, GETVAL));

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_48.c -o question48
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question48
Binary semaphore created successfully.
Semaphore ID: 0
Initial value: 1
*/