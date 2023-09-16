#pragma once

#include "types.h"

void sh_print_para(char **args);

char *sh_get_work_dir(void);

char *sh_read_line(void);

void *sh_input_preprocess(char *input_content);

void sh_split_line(char *input_content, char *tokens[ARR_LEN]);

void sh_data_preprocess(char **data);

void sh_para_addnull(char **para);