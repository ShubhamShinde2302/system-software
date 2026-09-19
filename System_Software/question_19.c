#include <stdio.h>
#include <unistd.h>

static inline unsigned long long rdtsc()
{
    unsigned int low, high;

    __asm__ volatile ("rdtsc"
                      : "=a"(low), "=d"(high));

    return ((unsigned long long)high << 32) | low;
}

int main()
{
    unsigned long long start, end;

    start = rdtsc();

    getpid();

    end = rdtsc();

    printf("Time taken by getpid(): %llu CPU cycles\n", end - start);

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_19.c -o question_19
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_19
Time taken by getpid(): 3174 CPU cycles
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_19
Time taken by getpid(): 3128 CPU cycles
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_19
Time taken by getpid(): 3014 CPU cycles

Note: rdtsc reads the CPU timestamp counter, so the number is a cycle count,
not microseconds, and it changes on every run. The count includes the two
rdtsc instructions themselves and any interruption by the scheduler, so an
occasional much larger value is normal. On systems where glibc serves
getpid() from cache the cost is far lower than a real system call.

==================================================== */
