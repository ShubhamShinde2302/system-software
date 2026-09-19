#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){

	int fd, flags;

	fd = open("file1.txt", O_RDWR | O_APPEND);

	if(fd < 0){
		perror("open");
		return 1;
	}

	flags = fcntl(fd, F_GETFL);

	if(flags < 0){
		perror("flags");
		close(fd);
		return 1;	
	}

	if((flags & O_ACCMODE) == O_RDONLY){
		printf("File Opened in Read Only Mode\n");
	}
	else if((flags & O_ACCMODE) == O_WRONLY){
		printf("File Opened in Write Only Mode\n");
	}
	else if((flags & O_ACCMODE) == O_RDWR){
		printf("File Opened in Read and Write Only Mode \n");
	}

	close(fd);

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_12.c -o question_12
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_12
File Opened in Read and Write Only Mode

Note: the file is opened with O_RDWR, so (flags & O_ACCMODE) == O_RDWR.
If the open() call is changed to O_RDONLY the output becomes
"File Opened in Read Only Mode", and with O_WRONLY it becomes
"File Opened in Write Only Mode".

==================================================== */
