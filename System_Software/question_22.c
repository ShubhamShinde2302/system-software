#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    pid_t pid;

    fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0)
    {
        write(fd, "Child process\n", 14);
    }
    else
    {
        write(fd, "Parent process\n", 15);
    }

    close(fd);

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_22.c -o question_22
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_22

(no output on the terminal, both processes write into the file)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat file.txt
Parent process
Child process

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l file.txt
-rw-r--r-- 1 shubham shubham 29 Sep 19 11:31 file.txt

Note: the file is opened before fork(), so parent and child share one open
file description and therefore one file offset. Neither write overwrites the
other and both lines survive. The order of the two lines can swap between
runs, since it depends on which process is scheduled first.

==================================================== */
