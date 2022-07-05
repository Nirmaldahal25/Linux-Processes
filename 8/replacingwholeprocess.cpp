#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if (pid < 0)
    {
        perror("Error occured while forking ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        int err = execlp("ls", "ls", "-altr", NULL);
        if (err == -1)
        {
            printf("Couldn't find ls to execute");
            exit(EXIT_FAILURE);
        }
        printf("hello wolrd\n"); // this line is ignored if execlp succeed else overlayed by the process execlp
    }
    else
    {

        wait(NULL);
    }
}