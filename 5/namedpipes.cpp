#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <type_traits>
#include <string.h>
#include <stdlib.h>

// problem related to mkfifo on windows
//  https://codeforces.com/blog/entry/86173

int main()
{
    int err = mkfifo("/tmp/fifo", S_IRWXU); // make FIFO file
    if (err != 0)
    {
        perror("couldn't create fifofile");
        exit(1);
    }
    int hello = fork();
    if (hello == 0)
    {
        char buff[20];
        const int fd = open("clientpid.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
        if (fd == -1)
            perror("Couldn't open clientpid");

        const int rd = open("/tmp/fifo", O_RDONLY);
        if (rd == -1)
            perror("Couldn't open file fifofile for reading");

        ssize_t rdsize = 1, wtsize = 0;
        while (rdsize > 0)
        {
            memset(buff, 0, 20);
            printf("read\n");
            rdsize = read(rd, buff, sizeof(buff));
            if (rdsize > 0)
            {
                printf("write\n");
                wtsize = write(fd, buff, rdsize);
            }
        }
        close(fd);
        close(rd);
    }
    else
    {
        const int fd = open("/tmp/fifo", O_WRONLY);
        if (fd == -1)
            perror("Couldn't open fifofile for writing");

        const char *buff[3] = {
            "My name is Random\n",
            "My name is Number\n",
            "My name is Hello World\n"};

        ssize_t wrsize;
        for (int i = 0; i < 3; i++)
        {
            wrsize = write(fd, buff[i], strnlen(buff[i], 40));
            if (wrsize != strnlen(buff[i], 50))
            {
                printf("Couldn't write to file\n");
            }
        }
        close(fd);
        wait(&hello);
    }
    unlink("fifofile.fifo");
}