#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signum)
{
    printf("\nCaught SIGINT: %d, interrupt occured\n", signum);
    exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Handler for SIGINT set, now running in infinite loop, press ctrl+c to trigger \n");

    while(1) sleep(1);

    return 0;
}
