#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void int_handler(int signum) {
    printf("\nCaught SIGINT: Interrupt signal received!\n");
    exit(0);
}

int main() {
    signal(SIGINT, int_handler);

    while (1) {
        printf("Running... Press Ctrl+C to trigger SIGINT.\n");
        sleep(2);
    }

    return 0;
}
