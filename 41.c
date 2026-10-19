#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msqid;

    key = ftok("/tmp", 'B');
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    printf("--- System V Message Queue ---\n");
    printf("Message Queue Key: %d (hex: 0x%x)\n", key, key);
    printf("Message Queue ID (msqid): %d\n", msqid);

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
    } else {
        printf("Message queue removed successfully.\n");
    }

    return 0;
}
