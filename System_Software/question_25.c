#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid[3];

    for (int i = 0; i < 3; i++)
    {
        pid[i] = fork();

        if (pid[i] < 0)
        {
            perror("fork");
            return 1;
        }

        if (pid[i] == 0)
        {
            printf("Child %d: PID = %d\n", i + 1, getpid());
            sleep(i + 1);
            printf("Child %d exiting\n", i + 1);
            exit(0);
        }
    }

    printf("Parent waiting for Child 2...\n");

    waitpid(pid[1], NULL, 0);

    printf("Child 2 finished. Parent continues.\n");

    for (int i = 0; i < 3; i++)
        waitpid(pid[i], NULL, 0);

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_25.c -o question_25
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_25
Child 1: PID = 4621
Child 2: PID = 4622
Parent waiting for Child 2...
Child 3: PID = 4623
Child 1 exiting
Child 2 exiting
Child 2 finished. Parent continues.
Child 3 exiting

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_25
Child 1: PID = 4630
Child 2: PID = 4631
Child 3: PID = 4632
Parent waiting for Child 2...
Child 1 exiting
Child 2 exiting
Child 2 finished. Parent continues.
Child 3 exiting

Note: each child sleeps i+1 seconds, so child 1 exits first, then child 2
after about 2 seconds, then child 3 after about 3 seconds. waitpid(pid[1])
blocks the parent until child 2 exits specifically, so "Parent continues"
always comes after "Child 2 exiting" and before "Child 3 exiting". The exact
position of the first "Parent waiting..." line and the PID values vary
between runs.

==================================================== */
