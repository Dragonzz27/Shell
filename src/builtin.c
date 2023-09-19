#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

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

void sh_builtin_export(char *src, char *dst)
{
    if (setenv(src, dst, 1))
    {
        perror("sh_builtin_export error!\n");
    }
}

void sh_builtin_export_append(char *src, char *dst)
{
    char *var = getenv(src);
    strcat(var, ":");
    strcat(var, dst);
    if (setenv(src, var, 1))
    {
        perror("sh_builtin_export_append error!\n");
    }
}

void sh_builtin_where(char *filename)
{
    struct dirent *entry;
    DIR *dir = opendir("/bin");
    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, filename))
        {
            printf("/bin/%s\n", entry->d_name);
        }
    }
    closedir(dir);
    dir = NULL;
    dir = opendir("/usr/bin");
    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, filename))
        {
            printf("/usr/bin/%s\n", entry->d_name);
        }
    }
    closedir(dir);
    dir = NULL;
    dir = opendir("./");
    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, filename))
        {
            printf("./%s\n", entry->d_name);
        }
    }
    closedir(dir);
    dir = NULL;
}

void sh_builtin_history()
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *history_path = (char *)calloc(STR_LEN, sizeof(char));
    strcpy(history_path, pwd->pw_dir);
    strcat(history_path, "/.fish/command_history.txt");

    FILE *fp = fopen(history_path, "r+");

    char *result = (char *)calloc(STR_LEN, sizeof(char));

    int cnt = 0;
    for (int i = 0; fgets(result, STR_LEN, fp) != NULL; i++)
    {
        cnt++;
    }
    fclose(fp);
    fp = NULL;

    fp = fopen(history_path, "r+");

    for (int i = 0; fgets(result, STR_LEN, fp) != NULL; i++)
    {
        // printf("[%d]: %s\n", i, result);
        if (i >= cnt - HIS_LEN)
        {
            printf("[%d]: %s", i - cnt + HIS_LEN + 1, result);
        }
    }
    free(history_path);
    history_path = NULL;
    fclose(fp);
    fp = NULL;
    free(result);
    result = NULL;
}

void sh_builtin_exit()
{
    exit(EXIT_SUCCESS);
}