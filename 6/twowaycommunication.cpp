#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Pipe(fd} failed");
        return 1;
    }

    int pid = fork();
    if (pid == 0)
    {
        char buff[20];
        memset(buff, 0, 20);
        const char *child = "Hello from Child";
        if (write(fd[1], child, strnlen(child, 20)) == -1)
        {
            return 2;
        }
        printf("Client Reading...\n"); // if it wasn't here child process would read data itself and parent wait for read in bocking mode
        if (read(fd[0], buff, sizeof(buff)) == -1)
        {
            printf("child exited without reading\n");
            return 3;
        }
        printf("%s\n", buff);
    }
    else
    {
        char buff[20];
        memset(buff, 0, 20);
        const char *child1 = "Hello from parent";
        if (read(fd[0], buff, sizeof(buff)) == -1)
        {
            return 4;
        }
        printf("%s\n", buff);
        printf("server writing...\n");
        if (write(fd[1], child1, strnlen(child1, 20)) == -1)
        {
            printf("Parent Sent data already\n");
            return 5;
        }
        printf("server wrote\n");
        wait(NULL);
    }
    close(fd[0]);
    close(fd[1]);
}