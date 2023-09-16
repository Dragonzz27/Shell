#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
    char *tokens[100];
    for (int i = 0; i < 100; i++)
    {
        tokens[i] = (char *)calloc(100, sizeof(char));
    }

    char *string = (char *)calloc(100, sizeof(char));
    strcpy(string, "Hello World! Hello World! ");
    char *token;

    printf("FLAG 1\n");
    token = strtok(string, " ");
    printf("FLAG 2\n");

    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
    printf("%s\n", string);

    return 0;
}