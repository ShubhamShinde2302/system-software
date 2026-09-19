#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


int main(){

	int fd;
	off_t pos;

	fd = open("file1.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	
	if(fd < 0){
		perror("open");
		return 1;
	}

	write(fd, "ABCDEFGHIJ", 10);

	pos = lseek(fd, 10, SEEK_CUR);


	if(pos == -1){
		perror("lseek");
		close(fd);
		return 1;
	}

	printf("File pointer is now at position : %ld\n", pos);

	write(fd, "KLMNOPQRST", 10);

	close(fd);

	return 0;


}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_10.c -o question_10
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_10
File pointer is now at position : 20

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ od -c file1.txt
0000000   A   B   C   D   E   F   G   H   I   J  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   K   L   M   N   O   P   Q   R   S   T
0000036

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l file1.txt
-rw-r--r-- 1 shubham shubham 30 Sep 19 11:11 file1.txt

Note: after writing 10 bytes the offset is 10, then lseek(fd, 10, SEEK_CUR)
moves it to 20. The gap from byte 10 to 19 is a "hole" and reads back as
zero bytes, which is why the file is 30 bytes long.

==================================================== */
