#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"ls", "-Rl", NULL};

    execv("/bin/ls", args);

    perror("execv");
    return 1;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_27D.c -o question_27D
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27D
.:
total 84
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 Notes.txt
-rwxr-xr-x 1 shubham shubham 16064 Sep 22 10:22 question_27D
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_27D.c
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_28.c
drwxr-xr-x 2 shubham shubham  4096 Sep 22 10:22 subdir

./subdir:
total 0
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 data.txt
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 log.txt

Note: execv() takes the argument list as an array (char *args[]) instead of
a NULL-terminated list of separate parameters like execl(), but it behaves
the same way and requires a full path to the binary, same as execl().

==================================================== */
