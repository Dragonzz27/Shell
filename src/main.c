#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>

#include "readline/history.h"
#include "readline/readline.h"

#include "utils.h"
#include "types.h"
#include "builtin.h"
#include "command.h"

#define CLOSE "\001\033[0m\002"
#define BLOD "\001\033[1m\002"
#define BEGIN(x, y) "\001\033[" #x ";" #y "m\002"

void sh_input_process(char **args)
{
    for (int i = 0; *(args + i) != NULL;)
    {
        char *para[STR_LEN];
        for (int j = 0; j < STR_LEN; j++)
        {
            para[j] = (char *)calloc(STR_LEN, sizeof(char));
        }
        char *filepath = (char *)calloc(STR_LEN, sizeof(char));
        int flag = 0;
        for (int j = i + 1; *(args + j) != NULL; j++)
        {
            if (!strcmp(*(args + j), ">"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], *(args + k));
                }
                para[j] = NULL;
                strcpy(filepath, *(args + j + 1));
                run_redirect_output_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(*(args + j), "2>"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], *(args + k));
                }
                para[j] = NULL;
                strcpy(filepath, *(args + j + 1));
                run_redirect_error_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(*(args + j), ">>"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], *(args + k));
                }
                para[j] = NULL;
                strcpy(filepath, *(args + j + 1));
                run_redirect_output_append_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(*(args + j), "<"))
            {
                sh_print_para(args);
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], *(args + k));
                }
                strcpy(filepath, *(args + j + 1));
                run_redirect_input_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(*(args + j), "<<"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], *(args + k));
                }
                para[j] = NULL;
                strcpy(filepath, *(args + j + 1));
                run_input_trunc_command(para, filepath);
                i = j + 2;
                flag = 1;
                break;
            }
            else if (!strcmp(*(args + j), "2>>"))
            {
                for (int k = i; k < j; k++)
                {
                    strcpy(para[k - i], *(args + k));
                }
                strcpy(filepath, args[j + 1]);
                run_redirect_error_append_command(para, filepath);
            }
            else if (!strcmp(*(args + j), "|"))
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
            for (int k = i; *(args + k) != NULL; k++)
            {
                strcpy(para[k - i], args[k]);
                cnt++;
            }
            free(para[cnt]);
            para[cnt] = NULL;
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

void sh_main_loop()
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *config_path = (char *)calloc(STR_LEN, sizeof(char));
    char *history_path = (char *)calloc(STR_LEN, sizeof(char));
    char *environment_path = (char *)calloc(STR_LEN, sizeof(char));
    char *tmp_data_path = (char *)calloc(STR_LEN, sizeof(char));
    strcat(config_path, pwd->pw_dir);
    strcat(config_path, "/.fish");

    if (access(config_path, F_OK))
    {
        mkdir(config_path, 0644);
    }

    strcat(history_path, pwd->pw_dir);
    strcat(history_path, "/.fish/command_history.txt");

    strcpy(environment_path, pwd->pw_dir);
    strcat(environment_path, "/.fish/environment.txt");

    strcpy(tmp_data_path, pwd->pw_dir);
    strcat(tmp_data_path, "/.fish/tmp_data.txt");

    read_history(history_path);
    while (1)
    {
        char *work_dir;
        char *input_content;
        char **args;

        work_dir = sh_get_work_dir();

        printf("\n");
        printf("%s\n", work_dir);

        input_content = readline(BEGIN(49, 36) BLOD "---> " CLOSE);
        add_history(input_content);
        write_history(history_path);

        sh_input_preprocess(input_content);
        args = sh_split_line(input_content);

        // for (int i = 0; *(args + i) != NULL; i++)
        // {
        //     printf("%s\n", *(args + i));
        // }

        sh_input_process(args);

        free(work_dir);
        free(input_content);
        free(args);
    }
    free(history_path);
    free(pwd);
}

int main(int argc, char **argv)
{
    sh_main_loop();
    return 0;
}