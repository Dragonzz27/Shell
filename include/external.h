#pragma once

void run_simple_command(char **para, int is_pipe_front, int is_run_background);

void run_redirect_output_command(char **para, char *filepath, int is_pipe_front, int is_run_background);

void run_redirect_output_append_command(char **para, char *filepath, int is_pipe_front, int is_run_background);

void run_redirect_input_command(char **para, char *filepath, int is_pipe_end, int is_run_background);

void run_input_trunc_command(char **para, char *delim, int is_pipe_front, int is_pipe_end, int is_run_background);

void run_redirect_error_command(char **para, char *filepath, int is_pipe_front, int is_run_background);

void run_redirect_error_append_command(char **para, char *filepath, int is_pipe_front, int is_run_background);

void run_redirect_output_error_command(char **para, char *filepath, int is_pipe_front, int is_run_background);

void run_redirect_pipeline_command(char **para, int is_pipe_front, int is_run_background);