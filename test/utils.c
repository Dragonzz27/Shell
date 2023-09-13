#include <unistd.h>
#include <stdlib.h>

char *sh_get_work_dir(void)
{
    char *work_dir;
    work_dir = (char *)malloc(100 * sizeof(char));
    getcwd(work_dir, 100);
    return work_dir;
}