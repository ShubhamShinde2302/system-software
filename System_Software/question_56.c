
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

// Read the CPU Time Stamp Counter
static inline uint64_t read_tsc_start(void)
{
    unsigned int low, high;

    __asm__ volatile(
        "lfence\n\t"
        "rdtsc"
        : "=a"(low), "=d"(high)
        :
        : "memory"
    );

    return ((uint64_t)high << 32) | low;
}

// Read the counter after the measured operations
static inline uint64_t read_tsc_end(void)
{
    unsigned int low, high, aux;

    __asm__ volatile(
        "rdtscp\n\t"
        "lfence"
        : "=a"(low), "=d"(high), "=c"(aux)
        :
        : "memory"
    );

    return ((uint64_t)high << 32) | low;
}

int main(void)
{
    uint64_t start, end;
    pid_t ppid = 0;

    // Measure 100 getppid() calls
    start = read_tsc_start();

    for (int i = 0; i < 100; i++) {
        ppid = getppid();
    }

    end = read_tsc_end();

    printf("Parent process ID: %d\n", (int)ppid);
    printf("Number of getppid() calls: 100\n");
    printf("Total TSC ticks: %llu\n",
           (unsigned long long)(end - start));
    printf("Average TSC ticks per call: %.2f\n",
           (double)(end - start) / 100.0);

    return 0;
}

/*
Output :

shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_56.c -o question56
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question56
Parent process ID: 7417
Number of getppid() calls: 100
Total TSC ticks: 116558
Average TSC ticks per call: 1165.58
*/
