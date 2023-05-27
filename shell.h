#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Buffer macros */
#define BFLUSH -1
#define WR_BSIZE 1024
#define RD_BSIZE 1024

/* Command chaining macros*/
#define NORM_CMD 0
#define OR_CMD 1
#define AND_CMD 2
#define CHAIN_CMD 3

/* System getline macros */
#define STR_TOK 0
#define GET_LINE 0
#define MAX_HIST 4096
#define FILE_HIST ".simple_shell_history"

/* Case Conversion Macros */
#define CONVTO_LOWER 1
#define CONVERT_UNSIGNED 2

/* External Environment */
extern char **environ;

/**
 * struct strlist - is function for linking the string list;
 * @num: is filed number;
 * @str: is our string to handle;
 * @next: is a pointer to the next node;
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} strl_t;

/**
 * struct passto - pass the commandline arguments to a function;
 * for allowing prototype to uniform structure functions;
 * @filename: is filename for a program;
 * @argc: is number of command line arguments;
 * @argv: is an array of strings to be obtained from args with cmd line infoma;
 * @arg: is a string containing command line arguments by getline;
 * @path: is a path of current command;
 * @env: is linked list of copy of all environment from environ;
 * @environ: is copy of all external local environment;
 * @changed_env: is a changed environment (environ);
 * @history: is node of histry containing histry;
 * @alias: is node of alias in local environment;
 * @status: is a status to be returned for condition of shell loop by execve;
 * @bf_cmd: on chaining as address of pointer of bf_cmd;
 * @cmdbf_type: is command type for OR (||), AND (&&), (;);
 * @readfd: is read line input for fdcr;
 * @count_line: is a counter for error line;
 * @nerror: error number for exit() functions;
 * @countline_flag: is flag counter in line command;
 * @count_hist: is for counting number of line history;
 */
typedef struct passto
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int nerror;
	int countline_flag;
	char *filename;
	strl_t *env;
	strl_t *history;
	strl_t *alias;
	char **environ;
	int changed_env;
	int status;
	char **bf_cmd;
	int cmdbf_type;
	int readfd;
	int count_hist;
} infto_t;

#define INIT_INFORMA \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}
/**
 * struct builtins - cointains a functions related to builtins struct;
 * @type: is type of builtin command;
 * @fx: is our function acronmy;
 */
typedef struct builtins
{
	char *type;
	int (*fx)(infto_t *);
} built_table;

/* 0-1-main.c prototypes */
int main(int ac, char **av);

/* 0-printings.c */
void print_string(char *str);
size_t print_linked_list(const strl_t *head);
size_t print_ls(const strl_t *head);
void _puts(char *str);

/* 0-string-actions.c */
int _strlen(char *s);
int custom_strcmp(char *str1, char *str2);
char *starts_with(const char *haystack, const char *needle);
char *custom_strncat(char *dest, char *src, int bytes);
char *custom_strchr(char *str, char c);

/* 0-string-manip.c */
char *custom_strcat(char *dest, char *src);
char *custom_strcpy(char *dest, char *src);
char *custom_strdup(const char *str);
char *custom_strncpy(char *dest, char *src, int n);
int string_replacer(char **old, char *new);

/* 0-writings.c */
int print_decimals(int input, int file_d);
int custom_putchar(char c);
int custom_error_putchar(char c);
int custom_put_filedescriptor(char c, int fdcr);
int custom_putsfd(char *str, int fdcr);

/* 1-cmd_interpreter.c */
int find_builtin_cmd(infto_t *infoma);
int hsh(infto_t *infoma, char **av);
char *memory_set(char *s, char b, unsigned int n);
void str_o_s_free(char **pp);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* 2-cmd-handle.c */
void custorm_fork(infto_t *infoma);
int is_executable(infto_t *infoma, char *path);
char *duplicate_char(char *path_txt, int start, int stop);
void cmnd_finder(infto_t *infoma);

/* 3-handle-path.c */
char *path_finder(infto_t *infoma, char *path_txt, char *cmd);
int is_interactive(infto_t *infoma);
int is_delimeter(char c, char *delim);
void error_printer(infto_t *infoma, char *estr);

/* 4-exit.c */
int exit_shell(infto_t *infoma);

/* 5-env.c */
int environ_printer(infto_t *infoma);
char *environ_getter(infto_t *infoma, const char *name);
int populate_envlist(infto_t *infoma);

/* 6-getline.c */
ssize_t input_buffer(infto_t *infoma, char **the_buffer, size_t *length);
ssize_t get_the_input(infto_t *infoma);
ssize_t buffer_reader(infto_t *infoma, char *the_buffer, size_t *i);
int custom_getline(infto_t *infoma, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);

/* 7-strtok.c */
char **str_to_words(char *str, char *delimiters);
int free_buffer(void **ptr);
char *custom_itoa(long int num, int base, int flags);

/* 8-exit-args.c */
int str_to_int(char *str);

/* 9-set_unset_env.c */
int misetenv(infto_t *infoma);
int miunsetenv(infto_t *infoma);
char **find_environ(infto_t *infoma);
int custom_unsetenv(infto_t *infoma, char *var);
int custom_setenv(infto_t *infoma, char *var, char *value);

/* 10-cd.c */
int _cd(infto_t *infoma);
int _help(infto_t *infoma);

/* 11-12-cmd_chaining.c */
int _ischain(infto_t *infoma, char *buffer, size_t *pt);
void chain_checker(infto_t *infoma, char *buffer,
				   size_t *pt, size_t i, size_t len);

/* 13-alias.c */
int mk_alias(infto_t *infoma, char *str);
int unmk_alias(infto_t *infoma, char *str);
int alias_replacer(infto_t *infoma);
int alias_printer(strl_t *node);
int _alias(infto_t *infoma);

/* 14-handle-vars-repl.c */
int var_replacer(infto_t *infoma);
void set_infoma(infto_t *infoma, char **av);
void free_infoma(infto_t *infoma, int yes);
void clear_infoma(infto_t *infoma);

/* 15-handle-comments.c */
void rm_comment(char *buffer);

/* 16-history.c */
char *file_history(infto_t *infoma);
int wr_history(infto_t *infoma);
int rd_history(infto_t *infoma);
int build_histls(infto_t *infoma, char *buffer, int linecounts);
int renum_hist(infto_t *infoma);

/* 16-listings.c */
strl_t *_addnode(strl_t **head, const char *str, int num);
strl_t *end_addnode(strl_t **head, const char *str, int num);
int del_nodeidx(strl_t **head, unsigned int index);
void free_lnlist(strl_t **p_hd);

/* 16-main-history.c */
int uhistory(infto_t *infoma);
size_t lnls_len(const strl_t *h);
char **str_list(strl_t *head);

/* 16-nodes.c */
strl_t *start_node(strl_t *node, char *prefix, char c);
ssize_t index_node(strl_t *head, strl_t *node);

#endif /* SHELL_H */
