
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void print_sysconf(const char *name, int option)
{
    errno = 0;
    long value = sysconf(option);

    if (value == -1) {
        if (errno == 0)
            printf("%-48s Indeterminate\n", name);
        else
            printf("%-48s Error: %s\n", name, strerror(errno));
    } else {
        printf("%-48s %ld\n", name, value);
    }
}

int main(void)
{
    printf("System Limitations and Configuration\n");
    printf("====================================\n");

    // 1. Maximum length of arguments for exec family
    print_sysconf("Maximum argument length (_SC_ARG_MAX)",
                  _SC_ARG_MAX);

    // 2. Maximum simultaneous processes per user ID
    print_sysconf("Maximum processes per user (_SC_CHILD_MAX)",
                  _SC_CHILD_MAX);

    // 3. Clock ticks per second
    print_sysconf("Clock ticks per second (_SC_CLK_TCK)",
                  _SC_CLK_TCK);

    // 4. Maximum number of open files
    print_sysconf("Maximum open files (_SC_OPEN_MAX)",
                  _SC_OPEN_MAX);

    // 5. Page size in bytes
    print_sysconf("Page size in bytes (_SC_PAGESIZE)",
                  _SC_PAGESIZE);

    // 6. Total number of physical pages
    print_sysconf("Total physical pages (_SC_PHYS_PAGES)",
                  _SC_PHYS_PAGES);

    // 7. Currently available physical pages
    print_sysconf("Available physical pages (_SC_AVPHYS_PAGES)",
                  _SC_AVPHYS_PAGES);

    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_57.c -o question57
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question57
System Limitations and Configuration
====================================
Maximum argument length (_SC_ARG_MAX)            2097152
Maximum processes per user (_SC_CHILD_MAX)       59444
Clock ticks per second (_SC_CLK_TCK)             100
Maximum open files (_SC_OPEN_MAX)                524288
Page size in bytes (_SC_PAGESIZE)                4096
Total physical pages (_SC_PHYS_PAGES)            3815803
Available physical pages (_SC_AVPHYS_PAGES)      748123
*/