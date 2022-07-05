#include <signal.h>
#include <iostream>
#include <unistd.h>

void sigsegvhandler(int sig) // kill -SIGSEGV <pid>
{
    // usecases:
    // properly close files that may prevent from erroneous text
    // free memory collected
    // send dependent processes, to stop working ...etc
    printf("%d sigsegv: I am not going to die. \n", sig);
}

void siginthandler(int sig) // kill -SIGINT <pid>
{
    printf("%d sigint: I am not going to die. ctrl + c \n", sig);
}

void sigkillhandler(int sig) // kill -SIGINT <pid>
{
    printf("%d sigkill: I am not going to die. No, I am dying. How did you do that. \n", sig);
}
int main()
{
    signal(SIGINT, siginthandler);
    signal(SIGSEGV, sigsegvhandler);
    signal(SIGKILL, sigkillhandler); // non maskable and isn't handled
    while (1)
    {
        sleep(1);
    }
}