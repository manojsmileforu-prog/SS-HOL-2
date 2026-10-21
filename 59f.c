#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void prof_handler(int signum) {
    printf("Caught SIGPROF: Profiling timer alarm received!\n");
    exit(0);
}

int main() {
    signal(SIGPROF, prof_handler);

    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    while (1) {
    }

    return 0;
}
