#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        sleep(5);

        printf("Child Process ID: %d\n", getpid());
        printf("New Parent Process ID: %d\n", getppid());
    }
    else
    {
        printf("Parent Process ID: %d\n", getpid());
        printf("Parent exiting...\n");
        exit(0);
    }

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_24.c -o question_24
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_24
Parent Process ID: 4501
Parent exiting...
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

(the shell prompt returns immediately, then 5 seconds later the orphaned
child prints into the same terminal)

Child Process ID: 4502
New Parent Process ID: 1

Note: the parent exits while the child is still in sleep(5), so the child is
orphaned. init/systemd adopts it, which is why getppid() returns 1 instead
of 4501. On some Ubuntu desktop sessions the adopting process is the user's
systemd instance, so the new parent ID can be that PID rather than 1.

==================================================== */
