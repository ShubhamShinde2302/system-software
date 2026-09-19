#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid;

	pid = fork();

	if(pid < 0){
		perror("fork");
		return 1;
	}
	else if(pid == 0){
		printf("Child process ID %d\n", getpid());
		printf("Parent Process Id %d\n\n", getppid());
	}
	else{
		printf("Parent Process  ID %d\n", getpid());
		printf("child Process ID %d\n", pid);
	}

	
	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_21.c -o question_21
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_21
Parent Process  ID 4382
child Process ID 4383
Child process ID 4383
Parent Process Id 4382

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_21
Parent Process  ID 4391
child Process ID 4392
Child process ID 4392
Parent Process Id 4391

Note: fork() returns 0 in the child and the child's PID in the parent, which
is why the child reports the same number the parent printed for it. The two
PIDs change on every run, and the order of the parent block and the child
block can swap because the scheduler decides which process runs first.

==================================================== */
