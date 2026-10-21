#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void myfunc(int signum)
{
    printf("Caught SIGSTOP signal: %d, exiting now \n", signum);
    exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = myfunc;
    sa.sa_flags = 0;

    printf("Changing the default SIGSTOP action to user defined function\n");
    sigaction(SIGSTOP, &sa, NULL);
    printf("Changed, now going into infinite loop, try killing me from another process, \n");

    while(1){
        sleep(3);
        printf("PID:%d still alive\n",getpid());
    }

    return 0;

}
