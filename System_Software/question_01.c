#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    // Create a soft link
    if (symlink("original.txt", "softlink.txt") == -1)
    {
        perror("symlink");
    }
    else
    {
        printf("Soft link created successfully.\n");
    }

    // Create a hard link
    if (link("original.txt", "hardlink.txt") == -1)
    {
        perror("link");
    }
    else
    {
        printf("Hard link created successfully.\n");
    }

    // Create a FIFO
    if (mkfifo("myfifo", 0666) == -1)
    {
        perror("mkfifo");
    }
    else
    {
        printf("FIFO created successfully.\n");
    }

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_01.c -o question_01

Run 1, in an empty directory (no original.txt yet):

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_01
Soft link created successfully.
link: No such file or directory
FIFO created successfully.

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l
total 16
prw-r--r-- 1 shubham shubham    0 Sep 22 11:10 myfifo
-rwxr-xr-x 1 shubham shubham 16120 Sep 22 11:10 question_01
lrwxrwxrwx 1 shubham shubham   12 Sep 22 11:10 softlink.txt -> original.txt

Note: symlink() does not care whether the target exists, so it succeeds and
creates a "dangling" link (ls -l shows it in a different colour because
original.txt is missing). link() requires original.txt to already exist, so
it fails with ENOENT and prints "link: No such file or directory".

Run 2, after creating original.txt and clearing the old link/fifo:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ echo "hello" > original.txt
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ rm -f softlink.txt hardlink.txt myfifo
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_01
Soft link created successfully.
Hard link created successfully.
FIFO created successfully.

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -li
total 24
573670 -rw-r--r-- 2 shubham shubham    6 Sep 22 11:12 hardlink.txt
573672 prw-r--r-- 1 shubham shubham    0 Sep 22 11:12 myfifo
573670 -rw-r--r-- 2 shubham shubham    6 Sep 22 11:12 original.txt
573669 -rwxr-xr-x 1 shubham shubham 16120 Sep 22 11:12 question_01
573671 lrwxrwxrwx 1 shubham shubham   12 Sep 22 11:12 softlink.txt -> original.txt

Note: hardlink.txt and original.txt share the same inode number (573670)
and both show a link count of 2, confirming they are two names for the same
file, unlike softlink.txt which has its own inode and just stores a path.

Run 3, running it again with all three targets already present:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_01
symlink: File exists
link: File exists
mkfifo: File exists

Note: once softlink.txt, hardlink.txt and myfifo all already exist, every
call fails with EEXIST, since none of symlink(), link() or mkfifo() will
overwrite an existing path.

==================================================== */
