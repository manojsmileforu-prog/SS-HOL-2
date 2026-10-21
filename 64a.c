#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void myfunc(void)
{
    printf("Caught SIGSTOP signal, exiting now \n");
    exit(1);
}

int main()
{
    struct sigaction sa;
    int pid;

    printf("This program will try to kill the other program, enter its process id\n");

    scanf("%d",&pid);

    printf("Got the pid, attempting to send the kill signal now\n");

    kill(pid, SIGSTOP);

    printf("sent the SIGSTOP signal via kill() \n");

    return 0;

}
