#include<stdio.h>
#include<sys/stat.h>
#include<time.h>


int main(){
	struct stat s;
	char fileName[100];

	printf("Enter File Name: ");
	scanf("%s" , fileName);

	if(stat(fileName, &s) < 0){
		perror("Stat");
		return 1;
	}

	printf("Inode number       : %ld\n", s.st_ino);
   	printf("Number of links    : %ld\n", s.st_nlink);
   	printf("UID                : %d\n", s.st_uid);
   	printf("GID                : %d\n", s.st_gid);
   	printf("Size               : %ld bytes\n", s.st_size);
   	printf("Block size         : %ld bytes\n", s.st_blksize);
   	printf("Number of blocks   : %ld\n", s.st_blocks);
    	printf("Last access time   : %s", ctime(&s.st_atime));
   	printf("Last modification  : %s", ctime(&s.st_mtime));
	printf("Last status change time : %s", ctime(&s.st_ctime));

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_9.c -o question_9
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_9
Enter File Name: file1.txt
Inode number       : 573631
Number of links    : 1
UID                : 1000
GID                : 1000
Size               : 29 bytes
Block size         : 4096 bytes
Number of blocks   : 8
Last access time   : Sat Sep 19 11:09:14 2026
Last modification  : Mon Sep  8 08:29:41 2026
Last status change time : Mon Sep  8 08:29:41 2026

Note: inode number, UID/GID and the timestamps depend on the machine and on
when the file was last touched, so these values will differ on every system.

==================================================== */
