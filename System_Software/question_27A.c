#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before execl\n");

    execl("/bin/ls", "ls", "-Rl", NULL);

    // If execl succeeds, this line is NEVER reached
    perror("execl failed");
    return 1;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_27A.c -o question_27A
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27A
Before execl
.:
total 84
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 Notes.txt
-rwxr-xr-x 1 shubham shubham 16056 Sep 22 10:22 question_27A
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_27A.c
-rw-r--r-- 1 shubham shubham     0 Sep 22 10:22 question_28.c
drwxr-xr-x 2 shubham shubham  4096 Sep 22 10:22 subdir

./subdir:
total 0
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 data.txt
-rw-r--r-- 1 shubham shubham 0 Sep 22 10:22 log.txt

Note: "Before execl" only shows up because stdout is line-buffered when it is
attached to a real terminal, so the '\n' flushes it before execl() replaces
the process image. If the program's output is piped or redirected to a file
(e.g. ./question_27A > out.txt), stdout becomes fully buffered instead, the
buffer is never flushed, and that line silently disappears from out.txt.
The actual listing shown above depends entirely on what is in the directory
question_27A is run from - here it is your ~/Desktop/LINUX folder.

Failure case, when /bin/ls does not exist at that exact path:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_27A
Before execl
execl failed: No such file or directory

Note: execl() only returns to the caller when it fails; on success the
process image is replaced and the lines after the call never run.

==================================================== */
