#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *fifo_name1 = "my_fifo_1";
    const char *fifo_name2 = "my_fifo_2";

   
    if (mknod(fifo_name1, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created using mknod: %s\n", fifo_name1);

    if (mkfifo(fifo_name2, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created using mkfifo: %s\n", fifo_name2);
    return 0;
}
