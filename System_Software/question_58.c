
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    int thread_num = *(int *)arg;

    printf("Thread %d created. Thread ID: %lu\n",
           thread_num, (unsigned long)pthread_self());

    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    int numbers[3] = {1, 2, 3};

    // Create three threads
    for (int i = 0; i < 3; i++) {
        int result = pthread_create(
            &threads[i],
            NULL,
            thread_function,
            &numbers[i]
        );

        if (result != 0) {
            printf("Failed to create thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for all three threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");

    return 0;
}
/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_58.c -o question58
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question58
Thread 2 created. Thread ID: 130203722442432
Thread 1 created. Thread ID: 130203730835136
Thread 3 created. Thread ID: 130203714049728
All threads completed.

*/