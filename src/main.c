#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STR_LEN 100

void sh_main_loop(void);

void sh_builtin_cd(char *path);
void sh_builtin_help(void);
void sh_builtin_exit(void);

char *sh_get_work_dir(void);

void run_simple_command(char **para);

char *sh_get_work_dir(void)
{
    char *work_dir;
    work_dir = (char *)malloc(STR_LEN * sizeof(char));
    getcwd(work_dir, STR_LEN);
    return work_dir;
}

void sh_builtin_cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("sh_builtin_cd_error");
    }
}

void sh_builtin_help()
{
    char *cmd[] = {
        "cd",
        "help",
        "exit",
    };
    for (int i = 0; *(cmd + i) != NULL; i++)
    {
        printf("%s\n", *(cmd + i));
    }
}

void sh_builtin_exit()
{
    return;
}

char *sh_read_line()
{
    char *line;
    line = (char *)malloc(STR_LEN * sizeof(char));
    fgets(line, STR_LEN, stdin);
    return line;
}

char **sh_split_line(char *input_content)
{
    int cnt = 0;
    char **tokens = (char **)malloc(STR_LEN * sizeof(char *));
    char *token;
    token = strtok(input_content, " \t\r\n");
    while (token != NULL)
    {
        tokens[cnt++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    tokens[cnt] = NULL;
    return tokens;
}

void *sh_input_preprocess(char *input_content)
{
    char tmp[STR_LEN];
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
}

void sh_print_para(char **args)
{
    for (int i = 0; *(args + i) != NULL; i++)
    {
        printf("%d\t%s\n", i, *(args + i));
    }
}

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

void sh_input_process(char **args)
{
    for (int i = 0; *(args + i) != NULL;)
    {
        char *para[STR_LEN];
        for (int j = 0; j < STR_LEN; j++)
        {
            para[j] = (char *)malloc(STR_LEN * sizeof(char));
        }
        char *filepath = (char *)malloc(STR_LEN * sizeof(char));
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
    while (1)
    {
        char *work_dir;
        char *input_content;
        char **args;

        work_dir = sh_get_work_dir();

        printf("\n");
        printf("%s\n", work_dir);
        printf("---> ");

        input_content = sh_read_line();
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
}

int main(int argc, char **argv)
{
    sh_main_loop();
    return 0;
}