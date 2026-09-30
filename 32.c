#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
	int fd[2];

	pipe(fd);

	char buff[] = "Hello my child, how are you? !! ";
	char read_buff[sizeof(buff)];
	
	pid_t p = fork();

	if (!p){
		close(fd[1]);
		read(fd[0], read_buff, sizeof(read_buff));
		printf("Message recieved from Parent (PID: %d) is %s\n",getppid(),read_buff);
	}
	else{
		close(fd[0]);
		write(fd[1], buff, sizeof(buff));
		printf("Message sent from parent!!\n");
	}
	return 0;
}
