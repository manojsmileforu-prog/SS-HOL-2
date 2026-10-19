   #include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char buffer[100];

    mkfifo("fifo_send", 0666);
    mkfifo("fifo_receive", 0666);

    printf("P1: Opening fifo_send...\n");
    fflush(stdout);
    int fd_send = open("fifo_send", O_WRONLY);

    printf("P1: Opening fifo_receive...\n");
    fflush(stdout);
    int fd_receive = open("fifo_receive", O_RDONLY);

    for (int i = 1; i <= 5; i++) {
        snprintf(buffer, sizeof(buffer),
                 "Message %d from P1\n", i);

        write(fd_send, buffer, strlen(buffer) + 1);
        printf("P1 sent: %s", buffer);

        ssize_t n = read(fd_receive, buffer, sizeof(buffer));
        if (n <= 0) break;

        buffer[n < (ssize_t)sizeof(buffer) ? n : sizeof(buffer) - 1] = '\0';
        printf("P1 received: %s", buffer);
    }

    close(fd_send);
    close(fd_receive);
    return 0;
}
