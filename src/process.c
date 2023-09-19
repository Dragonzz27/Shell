#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "utils.h"
#include "command.h"
#include "builtin.h"

void sh_input_process(char **tokens, int is_run_background)
{
    for (int i = 0; strcmp(tokens[i], "");)
    {
        int is_pipe_front = 0;
        int is_pipe_end = 0;
        if (i && !strcmp(tokens[i - 1], "|"))
        {
            is_pipe_front = 1;
        }
        char *para[ARR_LEN];
        for (int j = 0; j < ARR_LEN; j++)
        {
            para[j] = (char *)calloc(STR_LEN, sizeof(char));
        }
        char *filepath = (char *)calloc(STR_LEN, sizeof(char));
        char *var1 = (char *)calloc(STR_LEN, sizeof(char));
        char *var2 = (char *)calloc(STR_LEN, sizeof(char));
        int flag = 0;
        if (!strcmp(tokens[i], "cd"))
        {
            strcpy(filepath, tokens[i + 1]);
            sh_builtin_cd(filepath);
            i = i + 2;
        }
        else if (!strcmp(tokens[i], "exit"))
        {
            sh_builtin_exit();
            i = i + 1;
        }
        else if (!strcmp(tokens[i], "help"))
        {
            sh_builtin_help();
            i = i + 1;
        }
        else if (!strcmp(tokens[i], "history"))
        {
            sh_builtin_history();
            i = i + 1;
        }
        else if (!strcmp(tokens[i], "where"))
        {
            strcpy(filepath, tokens[i + 1]);
            sh_builtin_where(filepath);
            i = i + 2;
        }
        else if (!strcmp(tokens[i], "export"))
        {
            strcpy(var1, tokens[i + 1]);
            strcpy(var2, tokens[i + 3]);
            if (!strcmp(tokens[i + 2], "="))
            {
                sh_builtin_export(var1, var2);
            }
            else
            {
                sh_builtin_export_append(var1, var2);
            }
            i = i + 4;
        }
        else
        {
            for (int j = i + 1; strcmp(tokens[j], ""); j++)
            {
                if (!strcmp(tokens[j], ">"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    run_redirect_output_command(para, filepath, is_pipe_front, is_run_background);
                    i = j + 2;
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], "2>"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    run_redirect_error_command(para, filepath, is_pipe_front, is_run_background);
                    i = j + 2;
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], ">>"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    run_redirect_output_append_command(para, filepath, is_pipe_front, is_run_background);
                    i = j + 2;
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], "<"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    if (strcmp(tokens[j + 2], "") && !strcmp(tokens[j + 2], "|"))
                    {
                        is_pipe_end = 1;
                        i = j + 3;
                    }
                    else
                    {
                        i = j + 2;
                    }
                    run_redirect_input_command(para, filepath, is_pipe_end, is_run_background);
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], "<<"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    if (strcmp(tokens[j + 2], "") && !strcmp(tokens[j + 2], "|"))
                    {
                        is_pipe_end = 1;
                        i = j + 3;
                    }
                    else
                    {
                        i = j + 2;
                    }
                    run_input_trunc_command(para, filepath, is_pipe_front, is_pipe_end, is_run_background);
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], "2>>"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    run_redirect_error_append_command(para, filepath, is_pipe_front, is_run_background);
                    i = j + 2;
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], "2>&1"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    strcpy(filepath, tokens[j + 1]);
                    run_redirect_output_error_command(para, filepath, is_pipe_front, is_run_background);
                    i = j + 2;
                    flag = 1;
                    break;
                }
                else if (!strcmp(tokens[j], "|"))
                {
                    for (int k = i; k < j; k++)
                    {
                        strcpy(para[k - i], tokens[k]);
                    }
                    run_redirect_pipeline_command(para, is_pipe_front, is_run_background);
                    i = j + 1;
                    flag = 1;
                    break;
                }
                else
                {
                }
            }
            if (flag == 0)
            {
                int cnt = 0;
                for (int k = i; strcmp(tokens[k], ""); k++)
                {
                    strcpy(para[k - i], tokens[k]);
                    cnt++;
                }
                run_simple_command(para, is_pipe_front, is_run_background);
                break;
            }
        }
        for (int j = 0; j < STR_LEN; j++)
        {
            free(para[j]);
            para[j] = NULL;
        }
        free(filepath);
        filepath = NULL;
        free(var1);
        var1 = NULL;
        free(var2);
        var2 = NULL;
    }
}