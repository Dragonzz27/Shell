#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>

#include "types.h"

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
    strcpy(pipeline_path, pwd->pw_dir);
    strcat(pipeline_path, "/.fish/pipeline");
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
        if (ch == '<' || ch == '>' || ch == '|' || ch == '-')
        {
            if (pre_ch == '<' || pre_ch == '>' || pre_ch == '|' || pre_ch == '-')
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
            if (pre_ch == '<' || pre_ch == '>' || pre_ch == '|' || pre_ch == '&')
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