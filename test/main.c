#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        int fd = open("data.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
        close(1);
        dup(fd);
        execl("/bin/ls", "-l", NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        printf("Hello World!\n");
    }
}