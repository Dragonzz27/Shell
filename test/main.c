#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    setenv("TEST", "TRUE", 1);
    char *p = getenv("TEST");
    printf("PATH: %s\n", p);
    return 0;
}