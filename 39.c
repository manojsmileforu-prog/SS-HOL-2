#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#define FIFO_PATH "/tmp/my_fifo"

int main() {
    int fd;
    char buffer[256];
    fd_set read_fds;
    struct timeval timeout;

    mkfifo(FIFO_PATH, 0666);

    printf("Opening FIFO for reading (waiting for a writer)...\n");
    
    fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);

    printf("FIFO opened successfully. Waiting for data (timeout: 10 seconds)...\n");

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int activity = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (activity < 0) {
        perror("select error");
    } 
    else if (activity == 0) {
        printf("\n[TIMEOUT] No data was written to the FIFO within 10 seconds.\n");
    } 
    else {
        if (FD_ISSET(fd, &read_fds)) {
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                printf("\n[SUCCESS] Received data: %s", buffer);
            } else if (bytes_read == 0) {
                printf("\n[INFO] Writer closed the connection (EOF).\n");
            } else {
                perror("read error");
            }
        }
    }

    close(fd);
    unlink(FIFO_PATH);
    return 0;
}
