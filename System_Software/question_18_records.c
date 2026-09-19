#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

struct record{
	int id;
	char name[20];
};

int main(){
	
	int fd;

	struct record r[3] = {
		{1, "Bob"},
		{2, "Alice"},
		{3, "Charlie"}
	};


	fd = open("records.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);

	write(fd, r, sizeof(r));

	close(fd);

	return 0;

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_18_records.c -o question_18_records
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_18_records

(no output, the program just creates the data file)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l records.dat
-rw-r--r-- 1 shubham shubham 72 Sep 19 11:24 records.dat

Note: each struct record is 24 bytes (4 for the int, 20 for the name), so
three records take 72 bytes. Run this once before running question_18.c.

==================================================== */
