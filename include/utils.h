#pragma once

#include "types.h"

void sh_print_string(char *string);

void sh_print_para(char **args);

char *sh_get_work_dir(void);

char *sh_get_pipeline_path(void);

char *sh_read_line(void);

int sh_input_preprocess(char *input_content);

void sh_split_line(char *input_content, char *tokens[ARR_LEN]);

void sh_data_preprocess(char **data);

void sh_para_addnull(char **para);

void sh_signal_handler_sigint(int signum);

void sh_env_init(char *filepath);

void sh_path_split(char *path, char *paths[ARR_LEN]);

void sh_tokens_evaluate(char *tokens[ARR_LEN]);

char *sh_env_evaluate(char *token);