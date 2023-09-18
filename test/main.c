#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int pid;

void signal_handler_kill_child(int signum)
{
    printf("???\n");
    kill(pid, SIGKILL);
}

int main()
{
    signal(SIGINT, signal_handler_kill_child);
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        while (1)
        {
        };
    }
    else
    {

        int status;
        waitpid(pid, &status, 0);
        printf("Hello World!\n");
    }
}