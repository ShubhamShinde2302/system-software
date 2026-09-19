#include<unistd.h>

int main(){

	char buffer[100];

	int n = read(0, buffer, sizeof(buffer));

	write(1, buffer, n);

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_6.c -o question_6
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_6
Hello System Software
Hello System Software

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ echo "Hello System Software" | ./question_6
Hello System Software

Note: the first line is what the user typed, the second is what the program
wrote back to fd 1. read() returns after Enter is pressed.

==================================================== */
