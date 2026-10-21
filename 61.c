#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigsegv_handler(int signum)
{
    printf("Caught SIGSEGV: Segmentation fault occured\n");
    exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigsegv_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    int *ptr = NULL;
    *ptr = 42;

    return 0;
}
