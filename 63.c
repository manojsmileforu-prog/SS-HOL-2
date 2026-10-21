#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p = fork();

    if (p == 0)
    {
        printf("Child created successfully, PID: %d, my parent is: %d\n ", getpid(), getppid());

        sleep(1);

        kill(getppid(), SIGKILL);

        sleep(2);

        printf("Kill signal sent, child process is now orphan, it's parent is: %d\n", getppid());
    }
    else
    {
        printf("Parent process is running, pid: %d, waiting for child to send signal\n", getpid());

        wait(NULL);
    }

    return 0;
}
