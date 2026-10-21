#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void timer_handler (int signum)
{
    printf("Timer Expired! 10 seconds have passed.\n");
}


int main() {
    struct itimerval timer;

    signal(SIGALRM, timer_handler);

    timer.it_value.tv_sec = 10; //10 seconds
    timer.it_value.tv_usec = 0; // 0 microseconds

    setitimer(ITIMER_REAL, &timer, NULL);

    printf("Timer set for a 10-second interval, waiting for signals.. \n");

    while(1) pause();

    return 0;

}
