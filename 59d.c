#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void alrm_handler(int signum) {
    printf("Caught SIGALRM (via setitimer): Alarm signal received!\n");
    exit(0);
}

int main() {
    signal(SIGALRM, alrm_handler);

    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while (1) {
        printf("Waiting for timer...\n");
        sleep(1);
    }

    return 0;
}
