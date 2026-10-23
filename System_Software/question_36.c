    // 36. FIFO File Creation: Create a FIFO file using: 
    // a. mknod command 
    // b. mkfifo command 
    // c. Use strace command to determine which command (mknod or mkfifo) is more efficient. 
    // d. mknod system call 
    // e. mkfifo library function 
/*
Output mknod command:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ mknod fifo1 p
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ ls
System_Software  fifo1
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ ls -l
total 4
drwxrwxr-x 4 shubham shubham 4096 Oct 24 00:25 System_Software
prw-rw-r-- 1 shubham shubham    0 Oct 24 00:32 fifo1

*/

/*
Output mkfifo command:
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ mkfifo fifo2
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ ls -ls
total 4
4 drwxrwxr-x 4 shubham shubham 4096 Oct 24 00:25 System_Software
0 prw-rw-r-- 1 shubham shubham    0 Oct 24 00:32 fifo1
0 prw-rw-r-- 1 shubham shubham    0 Oct 24 00:34 fifo2
*/


/*
output strace command:

shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ strace -c mknod fifo3 p
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ------------------
 28.86    0.000537         537         1           execve
 20.58    0.000383          14        27           mmap
 10.21    0.000190          13        14           read
  8.65    0.000161          16        10         1 openat
  7.79    0.000145          18         8           mprotect
  3.22    0.000060           6         9           close
  3.12    0.000058           7         8           fstat
  2.42    0.000045          22         2           lseek
  2.15    0.000040          20         2           munmap
  1.93    0.000036           9         4           statx
  1.72    0.000032           3         9           rt_sigaction
  1.45    0.000027          13         2         2 statfs
  1.24    0.000023           7         3           brk
  0.91    0.000017           8         2         2 access
  0.81    0.000015           5         3           fcntl
  0.64    0.000012          12         1           poll
  0.59    0.000011           5         2           pread64
  0.59    0.000011           5         2           prlimit64
  0.54    0.000010           3         3           sigaltstack
  0.48    0.000009           9         1           prctl
  0.38    0.000007           7         1           arch_prctl
  0.38    0.000007           7         1           sched_getaffinity
  0.32    0.000006           6         1           getrandom
  0.27    0.000005           5         1           gettid
  0.27    0.000005           5         1           set_tid_address
  0.27    0.000005           5         1           set_robust_list
  0.21    0.000004           4         1           rseq
  0.00    0.000000           0         1           ioctl
  0.00    0.000000           0         1           mknodat
------ ----------- ----------- --------- --------- ------------------
100.00    0.001861          15       122         5 total
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software$ strace -c mkfifo fifo4
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ------------------
 26.05    0.000353          13        27           mmap
 11.51    0.000156          11        14           read
 10.18    0.000138          17         8           mprotect
 10.04    0.000136          13        10         1 openat
  5.09    0.000069          34         2           munmap
  4.72    0.000064          64         1           mknodat
  4.06    0.000055           6         9           close
  3.84    0.000052           6         8           fstat
  3.47    0.000047           5         9           rt_sigaction
  3.25    0.000044          22         2           lseek
  2.73    0.000037           9         4           statx
  1.62    0.000022           7         3           brk
  1.62    0.000022          11         2         2 statfs
  1.40    0.000019          19         1           chmod
  1.18    0.000016           5         3           sigaltstack
  1.11    0.000015           5         3           fcntl
  1.03    0.000014           7         2         2 access
  0.96    0.000013           6         2           umask
  0.81    0.000011           5         2           pread64
  0.74    0.000010          10         1           poll
  0.74    0.000010           5         2           prlimit64
  0.66    0.000009           9         1           prctl
  0.52    0.000007           7         1           ioctl
  0.52    0.000007           7         1           sched_getaffinity
  0.52    0.000007           7         1           getrandom
  0.37    0.000005           5         1           arch_prctl
  0.37    0.000005           5         1           rseq
  0.30    0.000004           4         1           gettid
  0.30    0.000004           4         1           set_tid_address
  0.30    0.000004           4         1           set_robust_list
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ------------------
100.00    0.001355          10       125         5 total
*/

// mknod system call

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>

int main() {
    if (mknod("fifo_syscall", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    printf("FIFO created successfully\n");
    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_36.c -o question36
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question36
FIFO created successfully
*/

// mkfifo library function

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    if (mkfifo("fifo_library", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created successfully\n");
    return 0;
}

/*
Output :
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ gcc question_36.c -o question36
shubham@shubham-Nitro-ANV15-52:~/Desktop/system-software/System_Software$ ./question36
FIFO created successfully
*/