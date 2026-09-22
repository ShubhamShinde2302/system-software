#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    pid_t pid;

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    // Parent exits
    if (pid > 0)
        exit(0);

    // Create new session
    setsid();

    // Change working directory
    chdir("/");

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {
        time_t now;
        struct tm *t;

        time(&now);
        t = localtime(&now);

        // Run script at 15:30
        if (t->tm_hour == 15 && t->tm_min == 30)
        {
            system("/home/shubham/Desktop/LINUX/system-software/System_Software/script.sh");
            break;
        }

        sleep(30);
    }

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_30.c -o question_30
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_30
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

(the shell prompt returns almost immediately - no other output appears)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ps -eo pid,ppid,sid,tty,stat,comm | grep question_30
    257      1    257 ?        Ss   question_30

Note: this program is a classic Unix daemon, so by design it produces no
terminal output at all. fork() creates a child, the original parent process
calls exit(0) right away (that is the "Parent exits" block), which is why
the shell prompt comes back instantly. The child calls setsid() to start a
new session and drop its controlling terminal (TTY shows as "?" in ps),
changes directory to "/", and closes fd 0, 1 and 2, so even printf() inside
it would go nowhere. It then sleeps in 30-second steps, checking the clock,
and only when the system time reaches 15:30 does it call
system(".../script.sh") and break out of the loop - if that script itself
prints anything, that output also goes nowhere, since stdout/stderr were
already closed. To actually see something happen, script.sh would need to
write to a log file rather than to stdout, and that file's contents (not
the terminal) is where the result of the 15:30 run would be visible:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat /home/shubham/Desktop/LINUX/system-software/System_Software/script.log
(depends entirely on what script.sh writes)

==================================================== */
