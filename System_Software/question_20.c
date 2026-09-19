#include <stdio.h>
#include <unistd.h>

int main()
{

    printf("ProcessID(ID): %d\n", getpid());
    while(1)
    {
        printf("Program is running...\n");
        sleep(2);
    }

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_20.c -o question_20
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_20
ProcessID(ID): 5612
Program is running...
Program is running...
Program is running...
Program is running...
^C
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

While it is running, from a second terminal:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ps -p 5612
    PID TTY          TIME CMD
   5612 pts/0    00:00:00 question_20

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ kill 5612

and the first terminal shows:

Terminated
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

Note: a new line appears every 2 seconds because of sleep(2). Ctrl+C sends
SIGINT and "kill" sends SIGTERM; either one ends the loop.

==================================================== */
