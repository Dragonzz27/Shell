#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <signal.h>

#include "types.h"
#include "builtin.h"

void sh_print_string(char *string)
{
    printf("%s\n", string);
}

void sh_print_para(char **tokens)
{
    for (int i = 0; strcmp(tokens[i], ""); i++)
    {
        printf("[%d] %s\n", i, tokens[i]);
    }
    printf("\n");
    printf("Result:\n");
}

char *sh_get_work_dir(void)
{
    char *work_dir = (char *)calloc(STR_LEN, sizeof(char));
    getcwd(work_dir, STR_LEN);
    return work_dir;
}

char *sh_get_pipeline_path(void)
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *pipeline_path = (char *)calloc(STR_LEN, sizeof(char));
    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcat(pipeline_path, "../config");
        strcat(pipeline_path, "/pipeline");
    }
    else
    {
        strcpy(pipeline_path, pwd->pw_dir);
        strcat(pipeline_path, "/.mysh/pipeline");
    }
    return pipeline_path;
}

char *sh_read_line()
{
    char *line = (char *)calloc(STR_LEN, sizeof(char));
    fgets(line, STR_LEN, stdin);
    return line;
}

int sh_input_preprocess(char *input)
{
    char *tmp = (char *)calloc(STR_LEN, sizeof(char));
    int cnt = 0;
    char pre_ch = 0;
    char ch = 0;
    int is_run_background = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        ch = input[i];
        if (ch == '<' || ch == '>' || ch == '|' || ch == '-' || ch == '=')
        {
            if (pre_ch == '<' || pre_ch == '>' || pre_ch == '|' || pre_ch == '-' || pre_ch == '=' || pre_ch == '+')
            {
                tmp[cnt++] = ch;
            }
            else
            {
                tmp[cnt++] = ' ';
                tmp[cnt++] = ch;
            }
        }
        else if (ch == '&')
        {
            is_run_background = 1;
        }
        else
        {
            if (pre_ch == '<' || pre_ch == '>' || pre_ch == '|' || pre_ch == '&' || pre_ch == '=')
            {
                tmp[cnt++] = ' ';
                tmp[cnt++] = ch;
            }
            else
            {
                tmp[cnt++] = ch;
            }
        }
        pre_ch = ch;
    }
    tmp[cnt] = 0;
    strcpy(input, tmp);
    free(tmp);
    tmp = NULL;
    return is_run_background;
}

void sh_split_line(char *input, char *tokens[ARR_LEN])
{
    int cnt = 0;
    char *token;
    token = strtok(input, " \t\r\n");
    while (token != NULL)
    {
        strcpy(tokens[cnt++], token);
        token = strtok(NULL, " \t\r\n");
    }
}

void sh_data_preprocess(char **data)
{
    for (int i = 0; strcmp(data[i], ""); i++)
    {
        int len = strlen(data[i]);
        data[i][len - 1] = 0;
    }
}

void sh_para_addnull(char **para)
{
    int cnt = 0;
    for (int i = 0; strcmp(para[i], ""); i++)
    {
        cnt++;
    }
    free(para[cnt]);
    para[cnt] = NULL;
}

void sh_signal_handler_sigint(int signum)
{
    if (GLOBAL_CHILD_PID)
    {
        kill(GLOBAL_CHILD_PID, SIGKILL);
        GLOBAL_CHILD_PID = 0;
    }
}

void sh_env_init(char *filepath)
{
    FILE *fp = fopen(filepath, "rw+");
    char *str = (char *)calloc(STR_LEN, sizeof(char));
    for (int i = 0; fgets(str, STR_LEN, fp) != NULL; i++)
    {
        char *tokens[ARR_LEN];
        for (int j = 0; j < ARR_LEN; j++)
        {
            tokens[j] = (char *)calloc(STR_LEN, sizeof(char));
        }
        sh_split_line(str, tokens);
        for (int j = 0; strcmp(tokens[j], ""); j++)
        {
            if (!strcmp(tokens[j], "export"))
            {
                if (!strcmp(tokens[j + 2], "="))
                {
                    sh_builtin_export(tokens[j + 1], tokens[j + 3]);
                    j = j + 4;
                }
                else
                {
                    sh_builtin_export_append(tokens[j + 1], tokens[j + 3]);
                    j = j + 4;
                }
            }
            else
            {
            }
        }
        for (int j = 0; j < ARR_LEN; j++)
        {
            free(tokens[j]);
            tokens[j] = NULL;
        }
    }
    free(str);
    str = NULL;
    fclose(fp);
    fp = NULL;
}

void sh_path_split(char *path, char *paths[ARR_LEN])
{
    int cnt = 0;
    char *var = strtok(path, ":");
    while (var != NULL)
    {
        strcpy(paths[cnt++], var);
        var = strtok(NULL, ":");
    }
}

char *sh_env_evaluate(char *token)
{
    char *tmp = (char *)calloc(STR_LEN, sizeof(char));
    strcpy(tmp, token + 1);
    const char *value = getenv(tmp);
    char *var_value = (char *)calloc(PATH_LEN, sizeof(char));
    strcpy(var_value, value);
    free(tmp);
    return var_value;
}

void sh_tokens_evaluate(char *tokens[ARR_LEN])
{
    for (int i = 0; strcmp(tokens[i], ""); i++)
    {
        if (tokens[i][0] == '$')
        {
            char *tmp = sh_env_evaluate(tokens[i]);
            free(tokens[i]);
            tokens[i] = (char *)calloc(PATH_LEN, sizeof(char));
            strcpy(tokens[i], tmp);
            free(tmp);
        }
    }
}

void sh_get_builtin_cmd(char *cmd[ARR_LEN])
{
    strcpy(cmd[0], "help");
    strcpy(cmd[1], "cd");
    strcpy(cmd[2], "exit");
    strcpy(cmd[3], "history");
    strcpy(cmd[4], "where");
    strcpy(cmd[5], "which");
    strcpy(cmd[6], "export");
    strcpy(cmd[7], "type");
}

void sh_tokens_alias(char *tokens[ARR_LEN])
{
    char *tmp_tokens[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        tmp_tokens[i] = (char *)calloc(STR_LEN, sizeof(char));
    }

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

    int cnt = 0;
    for (int i = 0; strcmp(tokens[i], ""); i++)
    {
        FILE *alias = fopen(alias_path, "r+");
        char *line = (char *)calloc(STR_LEN, sizeof(char));
        int flag = 0;
        for (int j = 0; fgets(line, STR_LEN, alias) != NULL; j++)
        {
            char *tmp = strtok(line, " \n");
            if (!strcmp(tokens[i], tmp))
            {
                while (tmp != NULL)
                {
                    if (strcmp(tmp, "="))
                    {
                        if (!flag)
                        {
                            flag = 1;
                        }
                        else
                        {
                            strcpy(tmp_tokens[cnt++], tmp);
                        }
                    }
                    tmp = strtok(NULL, " \n");
                }
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            strcpy(tmp_tokens[cnt++], tokens[i]);
        }

        free(line);
        line = NULL;
        fclose(alias);
        alias = NULL;
    }

    for (int i = 0; strcmp(tmp_tokens[i], ""); i++)
    {
        strcpy(tokens[i], tmp_tokens[i]);
    }
    free(alias_path);
    alias_path = NULL;
    for (int i = 0; i < ARR_LEN; i++)
    {
        free(tmp_tokens[i]);
        tmp_tokens[i] = NULL;
    }
}