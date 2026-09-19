#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){
	
	int fd;
	char ch;
	char line[100];
	int i = 0;
	int n;

	fd = open("file1.txt", O_RDONLY);
	
	if(fd < 0){
		perror("Error Opening File. \n");
		return 1;
	}


	while((n = read(fd, &ch, 1)) > 0){
		if(ch == '\n'){
			line[i] = '\0';
			printf("%s\n", line);
			i = 0;
		}
		else{
			line[i++] = ch;
		}
	}

	if(i > 0){
		line[i] = '\0';
		printf("%s \n",line);
	}

	close(fd);

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_8.c -o question_8
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat file1.txt
Hellow from fdHellow from fd1
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_8
Hellow from fdHellow from fd1

Note: the program reads one byte at a time and prints a line every time it
sees '\n'. file1.txt has no trailing newline, so the leftover characters are
printed by the final if(i > 0) block (that is why there is a trailing space).

With a file that does contain newlines:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ printf 'Line One\nLine Two\nLine Three\n' > file1.txt
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_8
Line One
Line Two
Line Three

==================================================== */
