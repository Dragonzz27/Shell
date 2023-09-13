#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

int main()
{
    printf("%s\n", sh_get_work_dir());
    return 0;
}