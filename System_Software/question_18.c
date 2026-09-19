#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record {
    int id;
    char name[20];
};

int main() {
    int fd, choice;
    struct record r;
    struct flock lock;

    fd = open("records.dat", O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Enter record number (1-3): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid record number.\n");
        close(fd);
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (choice - 1) * sizeof(struct record);
    lock.l_len = sizeof(struct record);

    printf("Waiting for lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Lock acquired.\n");

    lseek(fd, lock.l_start, SEEK_SET);

    if (read(fd, &r, sizeof(r)) == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Current Record: %d %s\n", r.id, r.name);

    printf("Enter new name: ");
    scanf("%s", r.name);

    lseek(fd, lock.l_start, SEEK_SET);

    if (write(fd, &r, sizeof(r)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("unlock");
        close(fd);
        return 1;
    }

    printf("Record updated and lock released.\n");

    close(fd);

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_18.c -o question_18
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_18_records
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_18
Enter record number (1-3): 2
Waiting for lock...
Lock acquired.
Current Record: 2 Alice
Enter new name: David
Record updated and lock released.

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_18
Enter record number (1-3): 2
Waiting for lock...
Lock acquired.
Current Record: 2 David
Enter new name: David
Record updated and lock released.

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_18
Enter record number (1-3): 5
Invalid record number.

Two processes locking different records do not block each other, because
the lock covers only 24 bytes starting at (choice - 1) * 24:

Terminal 1:                          Terminal 2:
Enter record number (1-3): 1         Enter record number (1-3): 3
Waiting for lock...                  Waiting for lock...
Lock acquired.                       Lock acquired.
Current Record: 1 Bob                Current Record: 3 Charlie

But if terminal 2 asks for record 1 as well, it stops at "Waiting for
lock..." until terminal 1 finishes.

==================================================== */
