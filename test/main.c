#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
    char *para[100];
    for (int i = 0; i < 100; i++)
    {
        para[i] = (char *)calloc(100, sizeof(char));
    }

    strcpy(para[0], "string0");
    strcpy(para[1], "string1");
    strcpy(para[2], "string2");

    for (int i = 0; strcmp(para[i], ""); i++)
    {
        printf("%s\n", para[i]);
    }

    for (int i = 0; i < 100; i++)
    {
        free(para[i]);
    }

    return 0;
}