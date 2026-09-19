#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	
	int fd;
	int ticket;
	struct flock lock;

	fd = open("ticket.txt", O_RDWR);

	if(fd < 0){
		perror("open");
		return 1;
	}

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	fcntl(fd, F_SETLKW, &lock);

	read(fd, &ticket, sizeof(ticket));
	
	ticket++;

	printf("New Ticket Number :%d\n", ticket);

	lseek(fd, 0, SEEK_SET);
	write(fd, &ticket, sizeof(ticket));

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return 0;

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_17_reserve.c -o question_17_reserve
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_17_store
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_17_reserve
New Ticket Number :101
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_17_reserve
New Ticket Number :102
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_17_reserve
New Ticket Number :103

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ od -An -tu4 ticket.txt
         103

Running several copies at the same time still gives unique numbers:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_17_reserve & ./question_17_reserve & ./question_17_reserve &
[1] 5310
[2] 5311
[3] 5312
New Ticket Number :104
New Ticket Number :105
New Ticket Number :106

Note: the F_WRLCK / F_SETLKW write lock serialises the read-increment-write
sequence, so no two processes can hand out the same ticket number.

==================================================== */
