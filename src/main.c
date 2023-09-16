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
#include "process.h"

#define CLOSE "\001\033[0m\002"
#define BLOD "\001\033[1m\002"
#define BEGIN(x, y) "\001\033[" #x ";" #y "m\002"

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
        mkdir(config_path, 0774);
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