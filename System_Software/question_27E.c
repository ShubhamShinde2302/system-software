#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"ls", "-Rl", NULL};

    execvp("ls", args);

    perror("execvp");
    return 1;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_27E.c -o question_27E
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27E
.:
total 100
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 Notes.txt
-rwxr-xr-x 1 shubham shubham 16056 Sep 22 10:22 question_27A
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_27A.c
-rwxr-xr-x 1 shubham shubham 16056 Sep 22 10:22 question_27B
-rwxr-xr-x 1 shubham shubham 16080 Sep 22 10:22 question_27C
-rwxr-xr-x 1 shubham shubham 16064 Sep 22 10:22 question_27D
-rwxr-xr-x 1 shubham shubham 16064 Sep 22 10:32 question_27E
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:32 question_27E.c
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_28.c
-rwxr-xr-x 1 shubham shubham 16384 Sep 22 10:22 question_30
drwxr-xr-x 2 shubham shubham  4096 Sep 22 10:22 subdir

./subdir:
total 0
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 data.txt
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 log.txt

Note: question_27E now calls execvp("ls", args) instead of execv(). Like
execlp() in 27B, execvp() searches the directories in $PATH for "ls" instead
of needing the full "/bin/ls" path, so the first argument no longer needs to
be an absolute path. The argument list is still passed as an array
(char *args[]), which is what distinguishes the "v" variants (execv,
execvp, execve) from the "l" variants (execl, execlp, execle) that take a
NULL-terminated list of separate arguments.

Failure case, if "ls" is not found anywhere on $PATH:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27E
execvp: No such file or directory

==================================================== */
