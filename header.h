#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

unsigned int get_str_len(char *str);
char *_strdup(char *str);
unsigned int _strlen(char *str);
unsigned int get_args(char *str);
unsigned int _strncmp(char *str1, char *str2, unsigned int n);
char *get_full_path(char *file, char **env);
char *get_path(char **env);
char *build_path(char *dir, char *file);

#endif /* HEADER_H */
