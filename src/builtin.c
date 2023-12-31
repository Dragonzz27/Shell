#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

#include "types.h"
#include "utils.h"

void sh_builtin_help()
{
    char *cmd[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        cmd[i] = (char *)calloc(STR_LEN, sizeof(char));
    }

    sh_get_builtin_cmd(cmd);

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
    char *paths[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        paths[i] = (char *)calloc(STR_LEN, sizeof(char));
    }
    char *var_path = (char *)calloc(PATH_LEN, sizeof(char));

    char *path = getenv("PATH");
    strcpy(var_path, path);
    sh_path_split(var_path, paths);

    struct dirent *entry;
    DIR *dir;
    for (int i = 0; strcmp(paths[i], ""); i++)
    {
        dir = opendir(paths[i]);
        if (dir == NULL)
        {
            continue;
        }
        while ((entry = readdir(dir)) != NULL)
        {
            if (!strcmp(entry->d_name, filename))
            {
                printf("%s/%s\n", paths[i], entry->d_name);
            }
        }
        closedir(dir);
        dir = NULL;
    }

    free(var_path);
    var_path = NULL;
    for (int i = 0; i < ARR_LEN; i++)
    {
        free(paths[i]);
        paths[i] = NULL;
    }
}

void sh_builtin_which(char *filename)
{
    char *paths[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        paths[i] = (char *)calloc(STR_LEN, sizeof(char));
    }
    char *var_path = (char *)calloc(PATH_LEN, sizeof(char));

    char *path = getenv("PATH");
    strcpy(var_path, path);
    sh_path_split(var_path, paths);

    struct dirent *entry;
    DIR *dir;
    for (int i = 0; strcmp(paths[i], ""); i++)
    {
        int flag = 0;
        dir = opendir(paths[i]);
        if (dir == NULL)
        {
            continue;
        }
        while ((entry = readdir(dir)) != NULL)
        {
            if (!strcmp(entry->d_name, filename))
            {
                printf("%s/%s\n", paths[i], entry->d_name);
                flag = 1;
                break;
            }
        }
        closedir(dir);
        dir = NULL;
        if (flag)
        {
            break;
        }
    }

    free(var_path);
    var_path = NULL;
    for (int i = 0; i < ARR_LEN; i++)
    {
        free(paths[i]);
        paths[i] = NULL;
    }
}

void sh_builtin_history()
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *history_path = (char *)calloc(STR_LEN, sizeof(char));
    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcpy(history_path, "../config");
        strcat(history_path, "/history");
    }
    else
    {
        strcpy(history_path, pwd->pw_dir);
        strcat(history_path, "/.mysh/history");
    }

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

void sh_builtin_type(char *filename)
{
    char *cmd[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        cmd[i] = (char *)calloc(STR_LEN, sizeof(char));
    }

    sh_get_builtin_cmd(cmd);

    int flag = 0;
    for (int i = 0; strcmp(cmd[i], ""); i++)
    {
        if (!strcmp(cmd[i], filename))
        {
            printf("%s is a shell builtin\n", filename);
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        sh_builtin_which(filename);
    }
}

void sh_builtin_exit()
{
    exit(EXIT_SUCCESS);
}

void sh_builtin_alias_add(char *var1, char *var2)
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *alias_path = (char *)calloc(STR_LEN, sizeof(char));
    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcpy(alias_path, "../config");
        strcat(alias_path, "/alias");
    }
    else
    {
        strcpy(alias_path, pwd->pw_dir);
        strcat(alias_path, "/.mysh/alias");
    }

    char *temporary_path = (char *)calloc(STR_LEN, sizeof(char));
    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcpy(temporary_path, "../config");
        strcat(temporary_path, "/temporary");
    }
    else
    {
        strcpy(temporary_path, pwd->pw_dir);
        strcat(temporary_path, "/.mysh/temporary");
    }

    FILE *alias = fopen(alias_path, "r+");
    if (access(temporary_path, F_OK))
    {
        remove(temporary_path);
    }
    FILE *temporary = fopen(temporary_path, "w+");
    char *line = (char *)calloc(STR_LEN, sizeof(char));
    char *tokens[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        tokens[i] = (char *)calloc(STR_LEN, sizeof(char));
    }
    int flag = 0;
    for (int i = 0; fgets(line, STR_LEN, alias) != NULL; i++)
    {
        int cnt = 0;
        char *tmp = strtok(line, " \n");
        while (tmp != NULL)
        {
            strcpy(tokens[cnt++], tmp);
            tmp = strtok(NULL, " \n");
        }

        if (!strcmp(tokens[0], var1))
        {
            flag = 1;
            for (int j = 0; strcmp(tokens[j], ""); j++)
            {
                fprintf(temporary, "%s ", tokens[j]);
            }
            fprintf(temporary, "%s \n", var2);
        }
        else
        {
            for (int j = 0; strcmp(tokens[j], ""); j++)
            {
                fprintf(temporary, "%s ", tokens[j]);
            }
            fprintf(temporary, "\n");
        }
    }
    if (!flag)
    {
        fprintf(temporary, "%s = %s %s\n", var1, var1, var2);
    }
    fclose(temporary);
    temporary = NULL;
    fclose(alias);
    alias = NULL;
    remove(alias_path);
    rename(temporary_path, alias_path);
    for (int i = 0; i < ARR_LEN; i++)
    {
        free(tokens[i]);
        tokens[i] = NULL;
    }
    free(line);
    line = NULL;
    free(temporary_path);
    temporary_path = NULL;
    free(alias_path);
    alias_path = NULL;
}

void sh_builtin_alias_delete(char *var1)
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *alias_path = (char *)calloc(STR_LEN, sizeof(char));
    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcpy(alias_path, "../config");
        strcat(alias_path, "/alias");
    }
    else
    {
        strcpy(alias_path, pwd->pw_dir);
        strcat(alias_path, "/.mysh/alias");
    }

    char *temporary_path = (char *)calloc(STR_LEN, sizeof(char));
    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcpy(temporary_path, "../config");
        strcat(temporary_path, "/temporary");
    }
    else
    {
        strcpy(temporary_path, pwd->pw_dir);
        strcat(temporary_path, "/.mysh/temporary");
    }

    FILE *alias = fopen(alias_path, "w+");
    if (access(temporary_path, F_OK))
    {
        remove(temporary_path);
    }
    FILE *temporary = fopen(temporary_path, "w+");
    char *line = (char *)calloc(STR_LEN, sizeof(char));
    char *tokens[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        tokens[i] = (char *)calloc(STR_LEN, sizeof(char));
    }
    for (int i = 0; fgets(line, STR_LEN, alias) != NULL; i++)
    {
        int cnt = 0;
        char *tmp = strtok(line, " \n");
        while (tmp != NULL)
        {
            strcpy(tokens[cnt++], tmp);
            tmp = strtok(NULL, " \n");
        }

        if (!strcmp(tokens[0], var1))
        {
            continue;
        }
        else
        {
            for (int j = 0; strcmp(tokens[j], ""); j++)
            {
                fprintf(temporary, "%s ", tokens[j]);
            }
            fprintf(temporary, "\n");
        }
    }
    fclose(temporary);
    temporary = NULL;
    fclose(alias);
    alias = NULL;
    remove(alias_path);
    rename(temporary_path, alias_path);
    for (int i = 0; i < ARR_LEN; i++)
    {
        free(tokens[i]);
        tokens[i] = NULL;
    }
    free(line);
    line = NULL;
    free(temporary_path);
    temporary_path = NULL;
    free(alias_path);
    alias_path = NULL;
}