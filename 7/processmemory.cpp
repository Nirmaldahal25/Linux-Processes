#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int a = 12; // before fork
    int *ptr = (int *)malloc(sizeof(int));
    int w = fork();
    if (w == 0) // child process
    {
        a = 13;
        *ptr = 13;
        printf("%d From Child\n", a);              // 13
        printf("%p : %d From Child\n", ptr, *ptr); // 13
    }
    else
    {
        sleep(5);
        printf("%d From Parent\n", a);              // 12
        printf("%p : %d From Parent\n", ptr, *ptr); // 12
        wait(NULL);
    }
    free(ptr);
}
