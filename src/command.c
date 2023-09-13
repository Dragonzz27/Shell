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
    int saved_stdout = dup(1);
    close(1);
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

    FILE *fd = fopen(filepath, "rw+");
    char *data[STR_LEN];
    for (int i = 0; i < STR_LEN; i++)
    {
        data[i] = (char *)malloc(STR_LEN * sizeof(char));
    }

    int data_len = 0;
    for (int i = 0; fgets(data[i], STR_LEN, fd) != NULL; i++)
    {
        data_len++;
    }
    int tmp_len = strlen(data[data_len - 1]);
    data[data_len - 1][tmp_len - 1] = 0;

    free(data[data_len]);
    data[data_len] = NULL;

    int cnt = 0;
    for (int i = 0; strcmp(*(para + i), ""); i++)
    {
        cnt++;
    }

    for (int i = 0; *(data + i) != NULL; i++)
    {
        strcpy(para[cnt + i], data[i]);
        cnt++;
    }

    free(para[cnt]);
    para[cnt] = NULL;

    int pid = fork();
    if (pid < 0)
    {
        printf("Create Process Fail!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
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
        fclose(fd);
    }
}

void run_input_trunc_command(char **para, char *delim)
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
        execvp(para[0], para);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
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