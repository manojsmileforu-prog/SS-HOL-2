#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void alrm_handler(int signum) {
    printf("Caught SIGALRM: Alarm signal received!\n");
    exit(0);
}

int main() {
    signal(SIGALRM, alrm_handler);

    alarm(3);

    while (1) {
        printf("Waiting for alarm...\n");
        sleep(1);
    }

    return 0;
}
