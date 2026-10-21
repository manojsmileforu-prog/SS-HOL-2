#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void my_handler( int sig){
    printf("I got SIGINT number: %d\n", sig);
    exit(0);
}

int main()
{
    signal(SIGINT, my_handler);

    printf("Catching SIGINT\n");
    sleep(3);
    printf("No SIGINT within 3 seconds\n");

    signal(SIGINT, SIG_IGN);
    printf("Ignoring SIGINT \n");
    sleep(3);
    printf("No SIGINT withing 3 seconds\n");

    signal(SIGINT, SIG_DFL); // reseting to default value for SIGINT
    printf("Default Action for SIGINT\n");
    sleep(3);
    printf("No SIGINT withing 3 seconds \n");

    return 0;
}
