#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

// creating child processes
int main()
{
    int client_pid = fork(); // create a new child process from here
    if (client_pid == 0)     // success fork returns 0 and error returns -1
    {
        printf("Hi, I am child process %d \n", getpid());
    }
    else
    {
        printf("Hi, I am parent process %d \n", getpid());
    }

    // {
    //     parent process    number of processes:1, process_no : 1
    //     fork();           number of processes:2, process_no : 1, 2
    //     fork();           number of processes:4, process_no: 3,4 and 1 creates 3 and 2 creates 4
    // }

    return 0;
}