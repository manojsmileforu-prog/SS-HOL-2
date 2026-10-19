  #include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char buffer[100];

    mkfifo("fifo_send", 0666);
    mkfifo("fifo_receive", 0666);

    printf("P2: Opening fifo_send for reading...\n");
    fflush(stdout);
    int fd_receive = open("fifo_send", O_RDONLY);

    printf("P2: Opening fifo_receive for writing...\n");
    fflush(stdout);
    int fd_send = open("fifo_receive", O_WRONLY);

    for (int i = 1; i <= 5; i++) {
        ssize_t n = read(fd_receive, buffer, sizeof(buffer));
        if (n <= 0) break;

        buffer[n < (ssize_t)sizeof(buffer) ? n : sizeof(buffer) - 1] = '\0';
        printf("P2 received: %s", buffer);

        snprintf(buffer, sizeof(buffer),
                 "Reply %d from P2\n", i);

        write(fd_send, buffer, strlen(buffer) + 1);
        printf("P2 sent: %s", buffer);
    }

    close(fd_send);
    close(fd_receive);
    return 0;
}
