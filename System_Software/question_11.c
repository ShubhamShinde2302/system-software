#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

	int fd, fd2;

	fd = open("file1.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

	if(fd < 0){
		perror("open");
		return 1;
	}


	fd2 = dup(fd);

	if(fd2 < 0){
		perror("dup");
		close(fd);
		return 1;
	}

	write(fd ,"Hellow from fd\n", 14);
	write(fd, "Hellow from fd1\n", 15);

	close(fd);
	close(fd2);

	return 0;

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_11.c -o question_11
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ > file1.txt
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_11

(the program prints nothing on the terminal, it writes to the file)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat file1.txt
Hellow from fdHellow from fd1shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l file1.txt
-rw-r--r-- 1 shubham shubham 29 Sep 19 11:13 file1.txt

Note: dup() makes fd2 refer to the same open file description as fd, so both
descriptors share one file offset and neither write overwrites the other.
The write counts are 14 and 15 while the strings are 15 and 16 bytes long,
so the '\n' of each string is not written, giving 29 bytes on one line.

==================================================== */
