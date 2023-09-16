 #pragma once

 void run_simple_command(char **para);

 void run_redirect_output_command(char **para, char *filepath);

 void run_redirect_output_append_command(char **para, char *filepath);

 void run_redirect_input_command(char **para, char *filepath);

 void run_input_trunc_command(char **para, char *delim);

 void run_redirect_error_command(char **para, char *filepath);

 void run_redirect_error_append_command(char **para, char *filepath);