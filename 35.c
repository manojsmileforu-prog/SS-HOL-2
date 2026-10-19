#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd1[2], fd2[2];
    pid_t pid1, pid2, pid3;

    pipe(fd1);
    pipe(fd2);

    pid1 = fork();

    if( pid1 == 0)
    {
        // child 1 executes ls -l
        close(fd1[0]); //closing unused read end
        dup2(fd1[1], 1); // cloning write end to STDOUT
        close(fd1[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("excelp"); // below lines only executes if excelp fails
        exit(1);
    }

    pid2 = fork();

    if(pid2 == 0)
    {
        //child 2 executes grep wc
        close (fd1[1]); //closing write end of pipe
        dup2 ( fd1[0], 0); // duplicate read end to the STDIN
        close(fd1[0]);

        close (fd2[0]); //closing write end of pipe
        dup2 ( fd2[1], 1); // duplicate read end to the STDIN
        close(fd2[0]);

        execlp("grep", "grep", "^d" , NULL);
        perror("exelcp(grep)");
        exit(1);
    }

    pid3 = fork();

    if(pid3 == 0)
    {
        close(fd1[0]);
        close(fd1[1]);

        close(fd2[1]);
        dup2(fd2[0], 0);
        close(fd2[0]);

        execlp("wc", "wc", NULL);
        perror("execlp(wc)");
        exit(1);
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);


    return 0;
}
