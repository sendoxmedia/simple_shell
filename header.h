#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

#define COMMAND_NOT_VALID 0
#define COMMAND_VALIDATED 1
#define VALID_COMMAND 2

unsigned int get_str_len(char *str);
char *_strdup(char *str);
unsigned int _strlen(char *str);
unsigned int _strncmp(char *str1, char *str2, unsigned int n);
char *get_full_path(char *file, char **env, char *shell);
char *get_path(char **env);
unsigned int get_args(char *str);
char *build_path(char *dir, char *file);
char *get_lineptr();
char **get_command(char *lineptr);
unsigned int validate_command(char **command, char *shell,
		char **env, int *exit_code);
void _free(char *lineptr, char **command, unsigned int free_command_0);
void print_error(char *shell, char *command);
int is_dir(char *command);

#endif /* HEADER_H */
