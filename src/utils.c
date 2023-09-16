#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types.h"

void sh_print_para(char **args)
{
    for (int i = 0; strcmp(args[i], ""); i++)
    {
        printf("%d\t%s\n", i, args[i]);
    }
}

char *sh_get_work_dir(void)
{
    char *work_dir = (char *)calloc(STR_LEN, sizeof(char));
    getcwd(work_dir, STR_LEN);
    return work_dir;
}

char *sh_read_line()
{
    char *line = (char *)calloc(STR_LEN, sizeof(char));
    fgets(line, STR_LEN, stdin);
    return line;
}

void *sh_input_preprocess(char *input_content)
{
    char *tmp = (char *)calloc(STR_LEN, sizeof(char));
    int cnt = 0;
    for (int i = 0; i < strlen(input_content); i++)
    {
        char pre_ch = 0;
        char ch = *(input_content + i);
        if (ch == '<' || ch == '>' || ch == '|' || ch == '-' || ch == '&')
        {
            if (pre_ch == '<' || ch == '>' || ch == '|' || ch == '-' || ch == '&')
            {
                tmp[cnt++] = ch;
            }
            else
            {
                tmp[cnt++] = ' ';
                tmp[cnt++] = ch;
            }
        }
        else
        {
            if (pre_ch == '<' || pre_ch == '>' || pre_ch == '|' || pre_ch == '-' || pre_ch == '&')
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
    strcpy(input_content, tmp);
    free(tmp);
}

char **sh_split_line(char *input_content)
{
    int cnt = 0;
    char **tokens = (char **)calloc(ARR_LEN, sizeof(char *));
    char *token;
    token = strtok(input_content, " \t\r\n");
    while (token != NULL)
    {
        tokens[cnt++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    return tokens;
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