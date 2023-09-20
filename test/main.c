#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());

    printf("%s\n", pwd->pw_dir);

    free(pwd);
    pwd = NULL;

    return 0;
}