#pragma once

void sh_builtin_cd(char *path);

void sh_builtin_help(void);

void sh_builtin_exit(void);

void sh_builtin_history(void);

void sh_builtin_where(char *filename);

void sh_builtin_which(char *filename);

void sh_builtin_export(char *src, char *dst);

void sh_builtin_export_append(char *src, char *dst);

void sh_builtin_type(char *filename);