
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
    key_t key;
    int shmid;
    char *ptr;

    // Generate a key
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create shared memory
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    printf("Shared Memory ID: %d\n", shmid);

    // Attach with read-write access
    ptr = (char *)shmat(shmid, NULL, 0);
    if (ptr == (char *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    // Write data
    strcpy(ptr, "Hello from shared memory!");
    printf("Data written: %s\n", ptr);

    // Detach read-write mapping
    if (shmdt(ptr) == -1) {
        perror("shmdt");
        return 1;
    }

    // Attach with read-only access
    ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (ptr == (char *)-1) {
        perror("shmat read-only");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    printf("Data read: %s\n", ptr);

    printf("Attempting to overwrite read-only memory is not safe.\n");
    printf("A write attempt can cause a protection fault (SIGSEGV).\n");

    // Detach read-only mapping
    if (shmdt(ptr) == -1) {
        perror("shmdt read-only");
        return 1;
    }

    printf("Shared memory detached successfully.\n");

    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        return 1;
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}
/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_47.c -o question47
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question47
Shared Memory ID: 35
Data written: Hello from shared memory!
Data read: Hello from shared memory!
Attempting to overwrite read-only memory is not safe.
A write attempt can cause a protection fault (SIGSEGV).
Shared memory detached successfully.
Shared memory removed successfully.
*/