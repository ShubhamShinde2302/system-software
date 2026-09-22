#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before execlp\n");

    execlp("ls", "ls", "-Rl", NULL);

    // If execlp succeeds, this line is NEVER reached
    perror("execlp failed");
    return 1;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_27B.c -o question_27B
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27B
Before execlp
.:
total 84
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 Notes.txt
-rwxr-xr-x 1 shubham shubham 16056 Sep 22 10:22 question_27B
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_27B.c
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_28.c
drwxr-xr-x 2 shubham shubham  4096 Sep 22 10:22 subdir

./subdir:
total 0
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 data.txt
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 log.txt

Note: execlp() is the only one of the five that searches $PATH for "ls"
instead of needing a full path, which is why the first argument here is
just "ls" and not "/bin/ls". If PATH did not contain a directory holding
ls, this would instead print:

Before execlp
execlp failed: No such file or directory

==================================================== */
