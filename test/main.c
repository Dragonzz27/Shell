#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    printf("Stdin: %d\n", stdin);
}