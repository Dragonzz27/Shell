#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>

#include "readline/history.h"
#include "readline/readline.h"

#include "utils.h"
#include "types.h"
#include "builtin.h"
#include "external.h"
#include "parser.h"

#define CLOSE "\001\033[0m\002"
#define BLOD "\001\033[1m\002"
#define BEGIN(x, y) "\001\033[" #x ";" #y "m\002"

#define NONE "\e[0m"
#define L_CYAN "\e[1;36m"
#define L_GREEN "\e[1;32m"
#define BG_WHITE "\e[47m"

void sh_main_loop()
{
    signal(SIGINT, sh_signal_handler_sigint);
    struct passwd *pwd;
    pwd = getpwuid(getuid());

    char *config_path = (char *)calloc(STR_LEN, sizeof(char));
    char *history_path = (char *)calloc(STR_LEN, sizeof(char));
    char *shellrc_path = (char *)calloc(STR_LEN, sizeof(char));
    char *pipeline_path = (char *)calloc(STR_LEN, sizeof(char));

    if (CONFIG_FILE_IN_CURRENT_DIR)
    {
        strcpy(config_path, "../config");

        strcpy(history_path, "../config");
        strcat(history_path, "/history");

        strcpy(shellrc_path, "../config");
        strcat(shellrc_path, "/shellrc");

        strcpy(pipeline_path, "../config");
        strcat(pipeline_path, "/pipeline");
    }
    else
    {
        strcpy(config_path, pwd->pw_dir);
        strcat(config_path, "/.mysh");

        strcpy(history_path, pwd->pw_dir);
        strcat(history_path, "/.mysh/history");

        strcpy(shellrc_path, pwd->pw_dir);
        strcat(shellrc_path, "/.mysh/shellrc");

        strcpy(pipeline_path, pwd->pw_dir);
        strcat(pipeline_path, "/.mysh/pipeline");
    }

    if (access(config_path, F_OK))
    {
        mkdir(config_path, 0774);
    }

    if (access(history_path, F_OK))
    {
        creat(history_path, 0774);
    }

    if (access(shellrc_path, F_OK))
    {
        creat(shellrc_path, 0774);
    }

    if (access(pipeline_path, F_OK))
    {
        creat(pipeline_path, 0774);
    }

    read_history(history_path);

    sh_env_init(shellrc_path);

    while (1)
    {
        char *work_dir;
        char *input;
        char *tokens[ARR_LEN];

        for (int i = 0; i < ARR_LEN; i++)
        {
            tokens[i] = (char *)calloc(STR_LEN, sizeof(char));
        }

        work_dir = sh_get_work_dir();

        printf("\n");
        printf(L_CYAN "%s\n" NONE, work_dir);

        input = readline(BEGIN(49, 36) BLOD L_GREEN "➞  " CLOSE);
        add_history(input);
        write_history(history_path);

        int is_run_background = sh_input_preprocess(input);

        sh_split_line(input, tokens);

        sh_tokens_evaluate(tokens);

        sh_print_para(tokens);

        sh_input_process(tokens, is_run_background);

        free(work_dir);
        work_dir = NULL;
        free(input);
        input = NULL;
        for (int i = 0; i < ARR_LEN; i++)
        {
            free(tokens[i]);
            tokens[i] = NULL;
        }
    }
    free(pipeline_path);
    pipeline_path = NULL;
    free(shellrc_path);
    shellrc_path = NULL;
    free(history_path);
    history_path = NULL;
    free(config_path);
    config_path = NULL;
}

int main(int argc, char **argv)
{
    sh_main_loop();
    return 0;
}