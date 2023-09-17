#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

void sh_builtin_help()
{
    char *cmd[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        cmd[i] = (char *)calloc(STR_LEN, sizeof(char));
    }
    strcpy(cmd[0], "help");
    strcpy(cmd[1], "cd");
    strcpy(cmd[2], "exit");

    for (int i = 0; strcmp(cmd[i], ""); i++)
    {
        printf("[%d]:\t%s\n", i, cmd[i]);
    }

    for (int i = 0; i < ARR_LEN; i++)
    {
        free(cmd[i]);
    }
}

void sh_builtin_cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("Sh Builtin Cd Error!\n");
    }
}

void sh_builtin_alias()
{
}

void sh_builtin_where()
{
}

void sh_builtin_exit()
{
    exit(EXIT_SUCCESS);
}