#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);

    struct msqid_ds buf;

    msgctl(msqid, IPC_STAT, &buf);
    printf("Current permissions: %o\n", buf.msg_perm.mode);

    buf.msg_perm.mode = 0777;
    msgctl(msqid, IPC_SET, &buf);

    msgctl(msqid, IPC_STAT, &buf);
    printf("New permissions: %o\n", buf.msg_perm.mode);

    return 0;
}
