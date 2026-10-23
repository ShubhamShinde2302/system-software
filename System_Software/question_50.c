
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t S1, S2;
pthread_barrier_t barrier;

void *thread1(void *arg)
{
    printf("Thread 1: Waiting for S1...\n");
    sem_wait(&S1);
    printf("Thread 1: Acquired S1.\n");

    // Wait until both threads have acquired their first semaphore
    pthread_barrier_wait(&barrier);

    printf("Thread 1: Waiting for S2...\n");
    sem_wait(&S2);

    printf("Thread 1: Acquired S2.\n");

    sem_post(&S2);
    sem_post(&S1);

    return NULL;
}

void *thread2(void *arg)
{
    printf("Thread 2: Waiting for S2...\n");
    sem_wait(&S2);
    printf("Thread 2: Acquired S2.\n");

    // Wait until both threads have acquired their first semaphore
    pthread_barrier_wait(&barrier);

    printf("Thread 2: Waiting for S1...\n");
    sem_wait(&S1);

    printf("Thread 2: Acquired S1.\n");

    sem_post(&S1);
    sem_post(&S2);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    // Initialize both semaphores to 1
    sem_init(&S1, 0, 1);
    sem_init(&S2, 0, 1);

    // Both threads must reach the barrier
    pthread_barrier_init(&barrier, NULL, 2);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // These statements are never reached during deadlock
    pthread_barrier_destroy(&barrier);
    sem_destroy(&S1);
    sem_destroy(&S2);

    return 0;
}

/*
Output:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_50.c -o question50
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question50
Thread 1: Waiting for S1...
Thread 1: Acquired S1.
Thread 2: Waiting for S2...
Thread 2: Acquired S2.
Thread 2: Waiting for S1...
Thread 1: Waiting for S2...

*/