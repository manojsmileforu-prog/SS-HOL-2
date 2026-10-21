#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void fpe_handler(int signum) {
    printf("Caught SIGFPE: Floating point exception occurred!\n");
    exit(1);
}

int main() {
    signal(SIGFPE, fpe_handler);

    int x = 1;
    int y = 0;
    int z = x / y;

    printf("Result: %d\n", z);

    return 0;
}
