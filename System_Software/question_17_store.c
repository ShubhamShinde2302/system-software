#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){
	int fd;
	int ticket = 100;

	fd = open("ticket.txt", O_RDWR | O_CREAT| O_TRUNC , 0644);

	if(fd < 0){
		perror("Open");
		return 1;
	}

	write(fd, &ticket, sizeof(ticket));
	
	close(fd);

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_17_store.c -o question_17_store
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_17_store

(no output, the program just initialises the counter file)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l ticket.txt
-rw-r--r-- 1 shubham shubham 4 Sep 19 11:20 ticket.txt

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ od -An -tu4 ticket.txt
         100

Note: the int 100 is written in binary, so ticket.txt is 4 bytes and
"cat ticket.txt" shows an unreadable character instead of the number.
Run this program once before running question_17_reserve.c.

==================================================== */
