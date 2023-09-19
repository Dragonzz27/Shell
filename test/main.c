#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    char *var1 = "PATH";
    char *var2 = "/home/dragonzz";
    if (setenv(var1, var2, 1))
    {
        printf("ERROR!\n");
    }
    char *p = getenv(var1);
    printf("PATH: %s\n", p);
    return 0;
}