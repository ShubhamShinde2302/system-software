#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("./hello", "./hello", "Shubham", NULL);

    perror("execl");
    return 1;
}

/*=================== OUTPUT ===================
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc a.c
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_26.c -o question_26
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_26 Shubham
Executing another executable...
Hello Shubham

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$
================================================ */
