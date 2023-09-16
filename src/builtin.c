#include <stdio.h>
#include <unistd.h>

void sh_builtin_cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("sh_builtin_cd_error");
    }
}

void sh_builtin_help()
{
    char *cmd[] = {
        "cd",
        "help",
        "exit",
    };
    for (int i = 0; *(cmd + i) != NULL; i++)
    {
        printf("%s\n", *(cmd + i));
    }

}

void sh_builtin_alias() {
    
}

void sh_builtin_where() {

}



void sh_builtin_exit()
{
    return;
}