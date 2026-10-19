#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct msg {
    long type;
    char text[80];
};

int main() {
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msg message;
    int flag_choice, mtype;

    printf("Choose flag:\n1.) 0 (blocking)\n2.) IPC_NOWAIT (non-blocking)\n=> ");
    scanf("%d", &flag_choice);

    printf("Enter message type to receive: ");
    scanf("%d", &mtype);

    int recv_flag = (flag_choice == 2) ? IPC_NOWAIT : 0;

    if (msgrcv(msqid, &message, sizeof(message.text), mtype, recv_flag) == -1) {
        perror("msgrcv");
    } else {
        printf("Received message: %s\n", message.text);
    }

    return 0;
}
