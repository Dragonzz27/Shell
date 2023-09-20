#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char *path = getenv("PATH");
    printf("%s\n", path);

    return 0;
}