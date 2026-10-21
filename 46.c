#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);

    int a = msgctl(msqid, IPC_RMID, NULL);
    if(a!=-1){
      printf("Deletion Successful");
    }
    
    return (0);
}
