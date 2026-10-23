
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

void lock_sem(int semid) {
    struct sembuf op = {0, -1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop lock");
        exit(1);
    }
}

void unlock_sem(int semid) {
    struct sembuf op = {0, 1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop unlock");
        exit(1);
    }
}

int main() {
    int semid, shmid;
    int *ticket;

    // Create semaphore and shared memory
    semid = semget(IPC_PRIVATE, 1, 0600);
    shmid = shmget(IPC_PRIVATE, sizeof(int), 0600);

    if (semid == -1 || shmid == -1) {
        perror("IPC creation");
        return 1;
    }

    // Initialize semaphore to 1
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        return 1;
    }

    ticket = (int *)shmat(shmid, NULL, 0);
    if (ticket == (void *)-1) {
        perror("shmat");
        return 1;
    }

    *ticket = 0;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        lock_sem(semid);

        // Critical section
        (*ticket)++;
        printf("Process %d generated ticket %d\n",
               (int)getpid(), *ticket);
        fflush(stdout);

        unlock_sem(semid);
        usleep(100000);
    }

    if (pid > 0)
        wait(NULL);

    shmdt(ticket);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question49
Process 29929 generated ticket 1
Process 29930 generated ticket 2
Process 29930 generated ticket 3
Process 29929 generated ticket 4
Process 29930 generated ticket 5
Process 29929 generated ticket 6
Process 29930 generated ticket 7
Process 29929 generated ticket 8
Process 29929 generated ticket 9
Process 29930 generated ticket 10
*/