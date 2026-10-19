    #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>

int main() {
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("--- Process File Limits ---\n");
        printf("Soft Limit (Current max open files): %lu\n", (unsigned long)limit.rlim_cur);
        printf("Hard Limit (Absolute max open files): %lu\n\n", (unsigned long)limit.rlim_max);
    } else {
        perror("getrlimit failed");
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    int pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);
    if (pipe_size != -1) {
        printf("--- Pipe Buffer Size ---\n");
        printf("Pipe capacity: %d bytes\n", pipe_size);
    } else {
        perror("fcntl F_GETPIPE_SZ failed");
    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
