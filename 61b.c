#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigfpe_hanlder(int signum)
{
    printf("\nCaught SIGFPE: Floating Point Exception occured\n");
    exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigfpe_hanlder;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    printf("Handler for SIGFPE set, now running an invalid operation\n");

    int a = 10, b = 0;
    int x = a/b;

    return 0;
}

