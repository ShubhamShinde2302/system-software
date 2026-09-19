#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	
	int fd;

	fd = creat("test.txt", 0644);

	if(fd == -1){
		printf("Error creating file");
		return 1;
	}

	printf("File Creation Successful \n");
	printf("File Descriptor %d \n:- ", fd);

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_3.c -o question_3
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_3
File Creation Successful
File Descriptor 3
:- shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l test.txt
-rw-r--r-- 1 shubham shubham 0 Sep 19 11:04 test.txt

Note: 0, 1 and 2 are already taken by stdin, stdout and stderr,
so creat() returns the lowest free descriptor, which is 3.
The last printf has no newline, so the shell prompt appears on the same line.

==================================================== */
