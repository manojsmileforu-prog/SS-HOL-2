#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];

    // Open the FIFO for reading
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

        while (1) {
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            printf("Received: %s", buffer);
        } else {
            break;         }
    }

   
    close(fd);

    // Optionally, remove the FIFO file
    unlink(FIFO_NAME);
    return 0;
}
