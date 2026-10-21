#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void vtalrm_handler(int signum) {
    printf("Caught SIGVTALRM: Virtual timer alarm received!\n");
    exit(0);
}

int main() {
    signal(SIGVTALRM, vtalrm_handler);

    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    printf("Entering busy wait till timer = %ld s runs out\n", (long)timer.it_value.tv_sec);

    while (1) {
    }

    return 0;
}
