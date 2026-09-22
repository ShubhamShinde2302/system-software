#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main()
{
    execle("/bin/ls", "ls", "-Rl", NULL, environ);

    perror("execle");
    return 1;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_27C.c -o question_27C
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27C
.:
total 84
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 Notes.txt
-rwxr-xr-x 1 shubham shubham 16080 Sep 22 10:22 question_27C
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_27C.c
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_28.c
drwxr-xr-x 2 shubham shubham  4096 Sep 22 10:22 subdir

./subdir:
total 0
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 data.txt
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 log.txt

Note: this file has no printf("Before...") call, so nothing is printed
before ls's own output, unlike question_27A/B. execle() is the only exec
variant that lets you pass a custom environment array explicitly instead of
inheriting the caller's environment automatically; here it is passed the
process's own environ, so the effect is the same as execl().

==================================================== */
