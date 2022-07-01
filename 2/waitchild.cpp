#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
// only parent process waits for child processes to complete
int main()
{
    // int id = fork();
    // if (id == 0)
    // {
    //     printf("Hi I am child %d \n", id);
    // }
    // else
    // {
    //     printf("Hi I am parent %d \n", id); //id in parent in is not equal to zero
    // }

    int a = fork();
    int b = fork();
    if (b == 0)
    {
        printf("Father and grandfather, don't wait for me I stop\n\n");
    }
    else // a and grandfather process
    {
        if (a != 0) // grandfather process
        {
            wait(&a);
            sleep(1);
            printf("Okay My dear children, Thank You for your help, I will miss you all.\n\n");
        }
        else // process a
        {
            wait(&b);
            printf("I will miss you son \n");
            printf("Father, Don't wait for me I stop\n\n");
        }
    }
}