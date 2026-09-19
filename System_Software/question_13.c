#include<stdio.h>
#include<sys/select.h>
#include<fcntl.h>


int main(){
	fd_set readfds;
	struct timeval timeout;

	FD_ZERO(&readfds);
	FD_SET(0, &readfds);

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	int ret = select(1, &readfds, NULL, NULL, &timeout);

	if(ret == -1){
		perror("select");
		return 1;
	}

	if(ret > 0){
		printf("Data is available on STDIN\n");
	}
	else if(ret == 0){
		printf("No data available within 10 seconds\n");
	}

	return 0;
	

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_13.c -o question_13

Run 1 - the user types something before the timeout expires:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_13
hello
Data is available on STDIN

Run 2 - the user types nothing and waits 10 seconds:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_13
No data available within 10 seconds

Note: select() returns the number of ready descriptors, or 0 when the
timeout expires first. End-of-file also counts as "ready", so
./question_13 < /dev/null immediately prints "Data is available on STDIN".

==================================================== */
