#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int main() {
    union semun arg;
    key_t key = ftok(".", 'a');
    
    int semid = semget(key, 1, IPC_CREAT | 0744);
    printf("Semaphore created with semid: %d\n", semid);

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    return 0;
}
