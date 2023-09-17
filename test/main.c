#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    char *string = "aa";
    printf("%ld\n", strlen(string));
    return 0;
}