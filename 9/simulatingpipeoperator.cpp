#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("Error Occured pipe occured");
        exit(0);
    }
    int pid = fork();
    if (pid < 0)
    {
        perror("Error occured while forking ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO); // duplicate write end to stdout
        int err = execlp("ls", "ls", "-altr", NULL);
        if (err == -1)
        {
            printf("Couldn't find ls to execute");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int pid2 = fork();
        if (pid2 < 0)
        {
            perror("error pid2 \n");
            exit(0);
        }
        else if (pid2 == 0)
        {
            dup2(fd[0], STDIN_FILENO); // duplicate read end to stdin
            int err = execlp("grep", "grep", "cmake", NULL);
            if (err == -1)
            {
                printf("Couldn't find ls to execute");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }
    close(fd[0]);
    close(fd[1]);
}