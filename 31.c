
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    char w_buff[80], r_buff[80];

    pipe(fd);

    printf("Enter data: ");
    scanf("%79[^\n]", w_buff);

    write(fd[1], w_buff, strlen(w_buff));

    int n = read(fd[0], r_buff, sizeof(r_buff) - 1);
    r_buff[n] = '\0';

    printf("Data read from pipe: %s\n", r_buff);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
