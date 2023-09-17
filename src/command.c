#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "types.h"
#include "utils.h"

void run_simple_command(char **para)
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

void run_redirect_output_command(char **para, char *filepath)
{
    printf("Run Redirect Output Command!\n");
    sh_print_para(para);
    // int saved_stdout = dup(1);
    // close(1);
    // int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    // dup(fd);
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        int saved_stdout = dup(1);
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
        // close(fd);
        // dup2(saved_stdout, 1);
        // close(saved_stdout);
    }
}

void run_redirect_output_append_command(char **para, char *filepath)
{
    printf("Run Redirect Output Append Command!\n");
    sh_print_para(para);
    int saved_stdout = dup(1);
    close(1);
    int fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 0644);
    dup(fd);
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        close(fd);
        dup2(saved_stdout, 1);
        close(saved_stdout);
    }
}

void run_redirect_input_command(char **para, char *filepath)
{
    printf("Run Redirect Input Command!\n");
    sh_print_para(para);
    FILE *fd = fopen(filepath, "rw+");
    char *data[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        data[i] = (char *)calloc(STR_LEN, sizeof(char));
    }

    for (int i = 0; fgets(data[i], STR_LEN, fd) != NULL; i++)
    {
    }

    sh_data_preprocess(data);

    int para_len = 0;
    for (int i = 0; strcmp(para[i], ""); i++)
    {
        para_len++;
    }

    for (int i = 0; strcmp(data[i], ""); i++)
    {
        strcpy(para[para_len + i], data[i]);
    }

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        for (int i = 0; i < STR_LEN; i++)
        {
            free(data[i]);
            data[i] = NULL;
        }
        fclose(fd);
        fd = NULL;
    }
}

void run_input_trunc_command(char **para, char *delim)
{
    printf("Run Input Trunc Command!\n");
    sh_print_para(para);

    char *data[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
    {
        data[i] = (char *)calloc(STR_LEN, sizeof(char));
    }

    for (int i = 0; fgets(data[i], STR_LEN, stdin); i++)
    {
    };

    int para_len = 0;
    for (int i = 0; strcmp(para[i], ""); i++)
    {
        para_len++;
    }

    for (int i = 0; strcmp(data[i], ""); i++)
    {
        int is_delim = 0;
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
            }
        }
        if (is_delim)
        {
            break;
        }
        else
        {
            strcpy(para[para_len + i], data[i]);
            para_len++;
        }
    }

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        for (int i = 0; i < STR_LEN; i++)
        {
            free(data[i]);
        }
    }
}

void run_redirect_error_command(char **para, char *filepath)
{
    printf("Run Redirect Error Command!\n");
    sh_print_para(para);
    int saved_stderr = dup(2);
    close(2);
    int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    dup(fd);
    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        close(fd);
        dup2(saved_stderr, 2);
        close(saved_stderr);
    }
}

void run_redirect_error_append_command(char **para, char *filepath)
{
    printf("Run Redirect Error Append Command!\n");
    sh_print_para(para);

    int saved_stderr = dup(2);
    close(2);
    int fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 0644);
    dup(fd);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        close(fd);
        dup2(saved_stderr, 2);
        close(saved_stderr);
    }
}

void run_redirect_output_error_command(char **para)
{
    printf("Run Redirect Output Error Append Command!\n");
    sh_print_para(para);

    int saved_stderr = dup(2);
    int saved_stdout = dup(1);
    close(1);
    dup(saved_stderr);
    close(2);
    dup(saved_stdout);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        close(1);
        dup2(saved_stdout, 1);
        close(saved_stdout);
        close(2);
        dup2(saved_stderr, 2);
        close(saved_stderr);
    }
}

void run_redirect_pipeline_command(char **para)
{
    printf("Run Redirect Pipeline Command!\n");
    sh_print_para(para);

    int saved_stdin = dup(0);
    int saved_stdout = dup(1);
    close(0);
    dup(saved_stdout);
    close(1);
    dup(saved_stdin);

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sh_para_addnull(para);
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        close(0);
        dup2(saved_stdin, 0);
        close(saved_stdin);
        close(1);
        dup2(saved_stdout, 1);
        close(saved_stdout);
    }
}