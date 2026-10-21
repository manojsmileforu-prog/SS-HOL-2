#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_handler(void)
{
    printf("Caught SIGINT, closing now.. \n");
    exit(1);
}

int main()
{
    struct sigaction sa;
    sa.sa_flags = 0;

    printf("First ignoring interrupt signal for 3 seconds, try pressing ctrl+c\n");

    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);

    sleep(3);

    printf("\nNow resetting to default behaviour, ctrl + c will terminate the program now \n");

    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);

    while(1) sleep(1);

    return 0;
}
