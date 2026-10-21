#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void timer_handler (int signum)
{
    printf("Timer Expired! 10 seconds of total time (CPU + real world) have passed.\n");
}


int main() {
    struct itimerval timer;

    signal(SIGPROF, timer_handler);

    timer.it_value.tv_sec = 10; //10 seconds
    timer.it_value.tv_usec = 0; // 0 microseconds

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    printf("Timer set for a 10-second (user CPU time +) interval, going into infinite loop.. \n");

    while(1) ;

    return 0;

}
