#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

// Foreground Process
//     The foregorund process takes keyboard inputs to run.
// Background Process
//     The backgorund process doesn't take keyboard inputs to run. A background process can be intitiated with ampersand(&)
//      operator while executing a executable.

// fg and bg commands are used to make a process foreground and background

int main() // parent process
{

    int a = fork(); // child process
    if (a == 0)
    {
        printf("Zombies incoming, Use kill command to kill this zombie %d", getpid());
        fflush(stdout);
        sleep(10);
    }
    else
    {
        // wait();
        exit(1); // make child process a zombie
    }
    return 0;
}
