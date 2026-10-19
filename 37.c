#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
       if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

       int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

        for (int i = 0; i < 5; i++) {
        snprintf(buffer, sizeof(buffer), "Message %d from sender\n", i + 1);
        write(fd, buffer, strlen(buffer) + 1); // +1 for null terminator
        sleep(1); // Sleep for a second before sending the next message
    }

  
    close(fd);
    return 0;
}
