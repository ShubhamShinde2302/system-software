#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	struct stat s;

	if(argc != 2){
		printf("Usage : %s <filename>\n", argv[0]);
		return 0;
	}


	if(lstat(argv[1], &s) == -1){
		perror("lstat");
		return 1;
	}


	   if (S_ISREG(s.st_mode))
       		 printf("Regular file\n");

  	  else if (S_ISDIR(s.st_mode))
  	  	 printf("Directory\n");

   	  else if (S_ISLNK(s.st_mode))
        	 printf("Symbolic link\n");

    	  else if (S_ISCHR(s.st_mode))
        	 printf("Character device\n");

    	  else if (S_ISBLK(s.st_mode))
        	 printf("Block device\n");

    	  else if (S_ISFIFO(s.st_mode))
         	 printf("FIFO (Named Pipe)\n");

    	  else if (S_ISSOCK(s.st_mode))
       		 printf("Socket\n");

          else
        	 printf("Unknown file type\n");

    	  return 0;

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_14.c -o question_14
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14
Usage : ./question_14 <filename>

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 file1.txt
Regular file

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 a
Directory

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ln -s file1.txt shortcut.txt
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 shortcut.txt
Symbolic link

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 /dev/null
Character device

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 /dev/sda
Block device

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ mkfifo mypipe
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 mypipe
FIFO (Named Pipe)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_14 /run/systemd/private
Socket

Note: lstat() is used instead of stat() so that a symbolic link is reported
as a link rather than as whatever it points to.

==================================================== */
