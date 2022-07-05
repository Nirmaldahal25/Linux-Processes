#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
/*  fd              parent              child1            child2
    fd[0]       rd: [0] wt:[1]      rd:[0] wt:[1]          NULL
    fd[1]       rd: [0] wt:[1]          NULL            rd:[0] wt:[1]
    fd[2]           NULL            rd:[0] wt:[1]       rd:[0] wt:[1]
*/

int main()
{
    int fd[3][2];               // C++ doesn't support Variable Length Arrays(VLA), use std::array with MSVC and Clang
    for (int i = 0; i < 3; i++) // No of Pipes pair is 6 depending upon fork implementation below
    {
        if (pipe(fd[i]) == -1)
        {
            perror("error instantiating pipes\n");
            exit(EXIT_FAILURE);
        }
    }
    char buff[20];
    memset(buff, 0, sizeof(buff));

    int a = fork(); // first child fork
    if (a < 0)
    {
        perror("First Child Fork Error\n");
        return 0;
    }
    if (a == 0)
    {
        close(fd[0][1]); // no writing to parent
        close(fd[1][0]); // parent and child2 relation
        close(fd[1][1]); // parent and child2 relation
        close(fd[2][0]); // no reading from Child2

        read(fd[0][0], buff, sizeof(buff)); // from parent
        printf("Child1: %s\n", buff);
        write(fd[2][1], buff, strnlen(buff, 20)); // to child2

        close(fd[0][0]);
        close(fd[2][1]);
    }
    else
    {
        int b = fork();
        if (b < 0)
        {
            perror("Second Child Fork Error\n");
            return 0;
        }
        if (b == 0) // child2
        {
            close(fd[0][0]); // parent and child1 relation
            close(fd[0][1]); // parent and child1 relation
            close(fd[1][0]); // no reading from parent
            close(fd[2][1]); // no writing to child1

            read(fd[2][0], buff, sizeof(buff)); // from child1
            printf("Child2: %s\n", buff);
            write(fd[1][1], buff, strnlen(buff, 20)); // to parent

            close(fd[2][0]);
            close(fd[1][1]);
        }
        else
        {
            const char *msg = "Hello From Parent";
            close(fd[0][0]); // no reading from child1
            close(fd[2][0]); // child1 and child2 relation
            close(fd[2][1]); // child1 and child2 relation
            close(fd[1][1]); // no writing to child2

            write(fd[0][1], msg, strnlen(msg, 20)); // to child1
            read(fd[1][0], buff, sizeof(buff));
            printf("Parent: %s\n", buff);

            close(fd[0][1]);
            close(fd[1][0]);
            wait(NULL);
        }
    }
}