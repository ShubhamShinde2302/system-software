
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_limit(const char *name, int resource)
{
    struct rlimit limit;

    if (getrlimit(resource, &limit) == -1) {
        perror(name);
        return;
    }

    printf("%-25s Soft limit: ", name);

    if (limit.rlim_cur == RLIM_INFINITY)
        printf("Unlimited");
    else
        printf("%llu", (unsigned long long)limit.rlim_cur);

    printf(", Hard limit: ");

    if (limit.rlim_max == RLIM_INFINITY)
        printf("Unlimited");
    else
        printf("%llu", (unsigned long long)limit.rlim_max);

    printf("\n");
}

int main(void)
{
    printf("System Resource Limits\n");
    printf("----------------------\n");

    print_limit("CPU time", RLIMIT_CPU);
    print_limit("File size", RLIMIT_FSIZE);
    print_limit("Data segment", RLIMIT_DATA);
    print_limit("Stack size", RLIMIT_STACK);
    print_limit("Core file size", RLIMIT_CORE);
    print_limit("Open files", RLIMIT_NOFILE);
    print_limit("Address space", RLIMIT_AS);
    print_limit("Processes", RLIMIT_NPROC);

    return 0;
}

/*
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_54.c -o question54
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question54
System Resource Limits
----------------------
CPU time                  Soft limit: Unlimited, Hard limit: Unlimited
File size                 Soft limit: Unlimited, Hard limit: Unlimited
Data segment              Soft limit: Unlimited, Hard limit: Unlimited
Stack size                Soft limit: 8388608, Hard limit: Unlimited
Core file size            Soft limit: 0, Hard limit: Unlimited
Open files                Soft limit: 524288, Hard limit: 524288
Address space             Soft limit: Unlimited, Hard limit: Unlimited
Processes                 Soft limit: 59444, Hard limit: 59444
*/