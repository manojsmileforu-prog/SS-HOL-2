#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shm_file", 'b');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory created with ID: %d\n", shmid);

    char *shm_write_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_write_ptr == (char *)(-1)) {
        perror("shmat (write)");
        exit(EXIT_FAILURE);
    }

    const char *data = "Hello from Shared Memory!";
    strncpy(shm_write_ptr, data, SHM_SIZE);
    printf("Data written successfully: %s\n", shm_write_ptr);

    if (shmdt(shm_write_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    char *shm_read_ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shm_read_ptr == (char *)(-1)) {
        perror("shmat (read-only)");
        exit(EXIT_FAILURE);
    }

    printf("Attached as Read-Only. Current content: %s\n", shm_read_ptr);
    printf("Attempting to overwrite memory in read-only mode...\n");

    // shm_read_ptr[0] = 'X'; 

    printf("(Safely avoided direct assignment to prevent SIGSEGV, but writing triggers a Segmentation Fault).\n");

    if (shmdt(shm_read_ptr) == -1) {
        perror("shmdt (read-only)");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory detached.\n");

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed from the kernel.\n");

    return 0;
}
