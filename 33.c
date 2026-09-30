#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fd1[2], fd2[2];

	pipe(fd1);
	pipe(fd2);


	char msg1[] = "Hello my child, how are you? !! ";
	char msg2[] = "Hello Father, I'm good.. ";
	char read_buff1[30];
	char read_buff2[30];

	pid_t p = fork();

	if (!p){ 
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0], read_buff1, sizeof(read_buff1));
		write(fd2[1], msg2 , sizeof(msg2));
		printf("Message recieved from Parent (PID: %d) is %s\n",getppid(),read_buff1);
	}
	else{ 
		close(fd1[0]);
		close(fd2[1]);
		write(fd1[1], msg1 , sizeof(msg1));
		printf("Message sent from parent!!\n");
		read(fd2[0], read_buff2, sizeof(read_buff2));
		printf("Child has replied: %s\n",read_buff2);
	}
	return 0;
}
