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
        printf("Child process: PID = %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent process: PID = %d\n", getpid());
        printf("Child process: PID = %d\n", pid);

        sleep(20);
    }

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_23.c -o question_23
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_23
Parent process: PID = 4431
Child process: PID = 4432
Child process: PID = 4432

(the program then sits in sleep(20))

From a second terminal while the parent is still sleeping:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ps -eo pid,ppid,stat,comm | grep question_23
   4431   3120 S    question_23
   4432   4431 Z    question_23

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ps -eo pid,stat,comm | grep defunct
   4432 Z    question_23 <defunct>

After 20 seconds the parent exits and the entry disappears:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ps -p 4432
    PID TTY          TIME CMD

Note: the child calls exit(0) but the parent never calls wait(), so the
child stays in the process table as a zombie, shown by state Z and the
"<defunct>" marker. When the parent exits, init/systemd adopts the child
and reaps it, so the zombie is cleaned up.

==================================================== */
