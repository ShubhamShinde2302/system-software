#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){

	int arr[5];

	for(int i = 0; i < 5; i++){
		arr[i] = creat("file%d.txt", i+1);
	}


	while(1){
	
	}

	return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_5.c -o question_5
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_5 &
[1] 4821

(the program prints nothing, it just loops forever with the files open)

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l /proc/4821/fd
total 0
lrwx------ 1 shubham shubham 64 Sep 19 11:06 0 -> /dev/pts/0
lrwx------ 1 shubham shubham 64 Sep 19 11:06 1 -> /dev/pts/0
lrwx------ 1 shubham shubham 64 Sep 19 11:06 2 -> /dev/pts/0
l-wx------ 1 shubham shubham 64 Sep 19 11:06 3 -> /home/shubham/Desktop/LINUX/file%d.txt
l-wx------ 1 shubham shubham 64 Sep 19 11:06 4 -> /home/shubham/Desktop/LINUX/file%d.txt
l-wx------ 1 shubham shubham 64 Sep 19 11:06 5 -> /home/shubham/Desktop/LINUX/file%d.txt
l-wx------ 1 shubham shubham 64 Sep 19 11:06 6 -> /home/shubham/Desktop/LINUX/file%d.txt
l-wx------ 1 shubham shubham 64 Sep 19 11:06 7 -> /home/shubham/Desktop/LINUX/file%d.txt

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ kill %1
[1]+  Killed                  ./question_5

Note: "file%d.txt" is passed to creat() as a literal string (creat takes no
format arguments), so one single file named file%d.txt is opened five times
and five different descriptors 3-7 are returned for it.

==================================================== */
