#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>

#define SIZE 1024
#define INITIAL_SIZE 10

/* Printings */
void print_string(char *str);
int _putchar(char c);
int custom_snprintf(char *str, size_t size, const char *format, ...);

/* Getting line handler */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **cmdtoargv(char *line);
void _execve(char **argv);
void _clear(void);
void exit_shell(void);

/* Environment handling prototype */
extern char **environ;
char *_which(const char *filename);
char *_getenv(const char *name);
void _printenv(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/* Tokenizing */
char *custom_strtok(char *str, const char *delimiters);

#endif /* SHELL_H */
