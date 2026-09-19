#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

	int src, dest;
	int n;
	char buffer[1000];

	src = open("file1", O_RDONLY);
	if(src < 0){
		perror("file1");
		return 1;
	}

	dest = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if(dest < 0){
		perror("file2");
		close(src);
		return 1;
	}

	while((n = read(src, buffer, sizeof(buffer))) > 0)
		write(dest, buffer, n);

	close(src);
	close(dest);

	printf("file Copied Successfully ,\n");
	return 0;

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_7.c -o question_7
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ echo "Hello World" > file1
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_7
file Copied Successfully ,

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat file2
Hello World

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ rm file1
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_7
file1: No such file or directory

Note: the source file is named "file1" (no .txt extension). If it does not
exist, open() fails and perror() prints the error above.

==================================================== */
