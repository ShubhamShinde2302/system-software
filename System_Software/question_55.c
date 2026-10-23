
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
    struct rlimit limit;

    // Set the soft and hard CPU time limits to 10 seconds
    limit.rlim_cur = 10;
    limit.rlim_max = 10;

    if (setrlimit(RLIMIT_CPU, &limit) == -1) {
        perror("setrlimit");
        return 1;
    }

    printf("CPU resource limit set successfully.\n");

    // Read back and display the limits
    if (getrlimit(RLIMIT_CPU, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("Soft CPU limit: %llu seconds\n",
           (unsigned long long)limit.rlim_cur);

    printf("Hard CPU limit: %llu seconds\n",
           (unsigned long long)limit.rlim_max);

    return 0;
}
/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_55.c -o question55
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question5
bash: ./question5: No such file or directory
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question55
CPU resource limit set successfully.
Soft CPU limit: 10 seconds
Hard CPU limit: 10 seconds
*/