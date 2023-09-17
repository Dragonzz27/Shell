#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#include "types.h"
#include "utils.h"

void run_simple_command(char **para, int is_pipe_front)
{
    printf("Run Simple Command!\n");
    sh_print_para(para);
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_output_command(char **para, char *filepath, int is_pipe_front)
{
    printf("Run Redirect Output Command!\n");
    sh_print_para(para);
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        close(1);
        int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
        dup(fd);
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_output_append_command(char **para, char *filepath, int is_pipe_front)
{
    printf("Run Redirect Output Append Command!\n");
    sh_print_para(para);
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        close(1);
        int fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 0644);
        dup(fd);
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_input_command(char **para, char *filepath, int is_pipe_end)
{
    printf("Run Redirect Input Command!\n");
    sh_print_para(para);

    int pid = fork();
    if (pid < 0)
    {

        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        FILE *fd = fopen(filepath, "r+");
        if (fd == NULL)
        {
            printf("No Such File!\n");
            exit(EXIT_FAILURE);
        }
        char *data[ARR_LEN];
        for (int i = 0; i < ARR_LEN; i++)
        {
            data[i] = (char *)calloc(STR_LEN, sizeof(char));
        }

        for (int i = 0; fgets(data[i], STR_LEN, fd) != NULL; i++)
        {
        }

        if (!is_pipe_end)
        {
            sh_data_preprocess(data);
        }

        int para_len = 0;
        for (int i = 0; strcmp(para[i], ""); i++)
        {
            para_len++;
        }

        for (int i = 0; strcmp(data[i], ""); i++)
        {
            strcpy(para[para_len + i], data[i]);
        }

        for (int i = 0; strcmp(para[i], ""); i++)
        {
            printf("%s\n", para[i]);
            for (int j = 0; j < strlen(para[i]); j++)
            {
                printf("%d ", para[i][j]);
            }
            printf("\n");
        }

        if (is_pipe_end)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
            close(1);
            dup(fd);
        }

        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_input_trunc_command(char **para, char *delim, int is_pipe_front, int is_pipe_end)
{
    printf("Run Input Trunc Command!\n");
    sh_print_para(para);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char *data[ARR_LEN];
        for (int i = 0; i < ARR_LEN; i++)
        {
            data[i] = (char *)calloc(STR_LEN, sizeof(char));
        }

        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            FILE *fp = fopen(path, "r+");
            for (int i = 0; fgets(data[i], STR_LEN, fp); i++)
            {
                printf("[%d]: %s\n", i, data[i]);
            }
        }
        else
        {
            for (int i = 0; fgets(data[i], STR_LEN, stdin); i++)
            {
            }
        }

        int para_len = 0;
        for (int i = 0; strcmp(para[i], ""); i++)
        {
            printf("[%d]: %s\n", i, para[i]);
            para_len++;
        }

        for (int i = 0; strcmp(data[i], ""); i++)
        {
            int is_delim = 0;
            char tmp[STR_LEN];
            for (int j = 0; j + strlen(delim) - 1 < strlen(data[i]); j++)
            {
                int flag = 0;
                for (int k = 0; k < strlen(delim); k++)
                {
                    if (data[i][j + k] == delim[k])
                    {
                        flag++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (flag == strlen(delim))
                {
                    is_delim = 1;
                    break;
                }
                tmp[j] = data[i][j];
                tmp[j + 1] = '\0';
            }
            if (is_delim)
            {
                strcpy(para[para_len++], tmp);
                break;
            }
            else
            {
                strcpy(para[para_len++], tmp);
            }
        }

        sh_print_para(para);

        if (is_pipe_end)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
            close(1);
            dup(fd);
        }

        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_error_command(char **para, char *filepath, int is_pipe_front)
{
    printf("Run Redirect Error Command!\n");
    sh_print_para(para);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
        close(2);
        dup(fd);
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_error_append_command(char **para, char *filepath, int is_pipe_front)
{
    printf("Run Redirect Error Append Command!\n");
    sh_print_para(para);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        int fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 0644);
        close(2);
        dup(fd);
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_output_error_command(char **para, char *filepath, int is_pipe_front)
{
    printf("Run Redirect Output Error Append Command!\n");
    sh_print_para(para);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
        close(1);
        dup(fd);
        close(2);
        dup(fd);
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void run_redirect_pipeline_command(char **para, int is_pipe_front)
{
    printf("Run Redirect Pipeline Command!\n");
    sh_print_para(para);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (is_pipe_front)
        {
            char *path = sh_get_pipeline_path();
            int fd = open(path, O_RDWR | O_CREAT, 0644);
            close(0);
            dup(fd);
        }
        struct passwd *pwd;
        pwd = getpwuid(getuid());
        char *path = (char *)calloc(STR_LEN, sizeof(char));
        strcpy(path, pwd->pw_dir);
        strcat(path, "/.fish/pipeline");
        int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
        close(1);
        dup(fd);
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}