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

#define SIZE 1024
#define INITIAL_SIZE 10

/* Getting line handler */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **cmdtoargv(char *line);
void _execve(char **argv);
void _clear(void);

/* Environment handling prototype */
extern char **environ;
char *_which(const char *filename);
char *_getenv(const char *name);
void _printenv(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif /* SHELL_H */
