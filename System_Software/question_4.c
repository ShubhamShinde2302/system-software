#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){

	int fd;

	fd = open("test.txt", O_WRONLY | O_CREAT |O_EXCL, 0644);


	if(fd == -1){
		printf("Error in Opening the file : \n");
		return 1;
	}

	printf("File Opened successfully: \n");
	printf("File Descriptor %d\n", fd);

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_4.c -o question_4
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ rm -f test.txt
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_4
File Opened successfully:
File Descriptor 3

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_4
Error in Opening the file :

Note: O_EXCL with O_CREAT makes open() fail if the file already exists,
so the second run fails with EEXIST.

==================================================== */
