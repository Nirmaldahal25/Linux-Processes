#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

// cannot use same file descriptor multiple times.
// cause write end of  file descriptor is closed to send signal to another process that the data is available for reading
int main()
{
    int fd[2]; // 0 read stream and 1 write stream
    if (pipe(fd) == -1)
    {
        printf("error occured opening pipe\n");
        exit(1);
    }

    int a = fork();
    if (a == 0)
    {
        char buff[40];
        close(fd[1]); // closing write stream
        printf(" I am waiting to read what parent sent me\n");
        read(fd[0], buff, sizeof(buff));
        printf("%s\n", buff);
        fflush(stdout); // flush stdout buffer to console
        close(fd[0]);
    }
    else
    {
        close(fd[0]); // closing read stream
        const char *dat = "hello from parent";
        write(fd[1], dat, strlen(dat));
        close(fd[1]); // send signal to other process that they can read from this pipe
    }
}