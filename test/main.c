#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    printf("%s\n", pwd->pw_dir);
    printf("%ld\n", pwd);
    free(pwd);
    return 0;
}