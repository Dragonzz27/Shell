#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "utils.h"
#include "command.h"

void sh_input_process(char **tokens)
{
    for (int i = 0; strcmp(tokens[i], "");)
    {
        char *para[ARR_LEN];
        for (int j = 0; j < ARR_LEN; j++)
        {
            para[j] = (char *)calloc(STR_LEN, sizeof(char));
        }
        char *filepath = (char *)calloc(STR_LEN, sizeof(char));
        int flag = 0;
        for (int j = i + 1; strcmp(tokens[j], ""); j++)
        {
            if (!strcmp(tokens[j], ">"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], tokens[k]);
                }
                strcpy(filepath, tokens[j + 1]);
                run_redirect_output_command(para, filepath);
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
                run_redirect_error_command(para, filepath);
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
                run_redirect_output_append_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(tokens[j], "<"))
            {
                sh_print_para(tokens);
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], tokens[k]);
                }
                strcpy(filepath, *(tokens + j + 1));
                run_redirect_input_command(para, filepath);
                i = j + 2;
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
                run_input_trunc_command(para, filepath);
                i = j + 2;
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
                run_redirect_error_append_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(tokens[j], "2&>1"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], tokens[k]);
                }
                run_redirect_output_error_command(para);
                i = j + 1;
                flag = 1;
                break;
            }
            else if (!strcmp(tokens[j], "|"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], tokens[k]);
                }
                run_redirect_pipeline_command(para);
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
            run_simple_command(para);
            break;
        }
        for (int j = 0; j < STR_LEN; j++)
        {
            free(para[j]);
            para[j] = NULL;
        }
        free(filepath);
        filepath = NULL;
    }
}