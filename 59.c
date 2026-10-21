#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segv_handler(int signum) {
    printf("Caught SIGSEGV: Segmentation fault occurred!\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, segv_handler);

    int *ptr = NULL;
    *ptr = 42;

    return 0;
}
