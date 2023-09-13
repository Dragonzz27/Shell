#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *args[10];
    for (int i = 0; i < 10; i++)
    {
        args[i] = (char *)malloc(100 * sizeof(char));
    }
    printf(">>>\n");
    strcpy(args[0], "string1");
    strcpy(args[1], "string2");
    strcpy(args[2], "string3");
    free(args[3]);
    args[3] = NULL;

    for (int i = 0; args[i] != NULL; i++)
    {
        printf("%d %s\n", i, *(args + i));
    }

    for (int i = 0; i < 10; i++)
    {
        free(args[i]);
    }

    return 0;
}