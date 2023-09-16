#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"
#include "command.h"

void sh_input_process(char **args)
{
    for (int i = 0; strcmp(args[i], "");)
    {
        char *para[ARR_LEN];
        for (int j = 0; j < ARR_LEN; j++)
        {
            para[j] = (char *)calloc(STR_LEN, sizeof(char));
        }
        char *filepath = (char *)calloc(STR_LEN, sizeof(char));
        int flag = 0;
        for (int j = i + 1; strcmp(args[j], ""); j++)
        {
            if (!strcmp(args[j], ">"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], args[k]);
                }
                strcpy(filepath, args[j + 1]);
                run_redirect_output_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(args[j], "2>"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], args[k]);
                }
                strcpy(filepath, args[j + 1]);
                run_redirect_error_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(args[j], ">>"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], args[k]);
                }
                strcpy(filepath, args[j + 1]);
                run_redirect_output_append_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(args[j], "<"))
            {
                sh_print_para(args);
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], args[k]);
                }
                strcpy(filepath, *(args + j + 1));
                run_redirect_input_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(args[j], "<<"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], args[k]);
                }
                strcpy(filepath, args[j + 1]);
                run_input_trunc_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(args[j], "2>>"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], args[k]);
                }
                strcpy(filepath, args[j + 1]);
                run_redirect_error_append_command(para, filepath);
            }
            else if (!strcmp(args[j], "|"))
            {
                break;
            }
            else
            {
            }
        }
        if (flag == 0)
        {
            int cnt = 0;
            for (int k = i; args[k] != NULL; k++)
            {
                strcpy(para[k - i], args[k]);
                cnt++;
            }
            run_simple_command(para);
            break;
        }
        for (int j = 0; j < STR_LEN; j++)
        {
            free(para[j]);
        }
        free(filepath);
    }
}