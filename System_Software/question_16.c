#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, choice;
    struct flock lock;

    fd = open("file1.txt", O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("1. Read Lock\n");
    printf("2. Write Lock\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    lock.l_type = (choice == 1) ? F_RDLCK : F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Waiting for lock...\n");

    fcntl(fd, F_SETLKW, &lock);

    printf("Lock acquired. Press Enter to release...\n");
    getchar();
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_16.c -o question_16

Terminal 1:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_16
1. Read Lock
2. Write Lock
Enter choice: 2
Waiting for lock...
Lock acquired. Press Enter to release...

Terminal 2 (started while terminal 1 still holds the write lock):

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_16
1. Read Lock
2. Write Lock
Enter choice: 2
Waiting for lock...

(terminal 2 stays blocked here)

Back in terminal 1, pressing Enter releases the lock:

Lock acquired. Press Enter to release...
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

and terminal 2 immediately continues:

Lock acquired. Press Enter to release...

Single run with no other process holding a lock:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_16
1. Read Lock
2. Write Lock
Enter choice: 1
Waiting for lock...
Lock acquired. Press Enter to release...

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

Note: F_SETLKW blocks until the lock can be taken. Two read locks (choice 1)
can be held at the same time, but a write lock is exclusive.

==================================================== */
