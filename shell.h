#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define PROMPT "$ "
#define DELIMITERS " \t\n\v\f\r"
#define NEWLINE "\n"
#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct builtin_t - Struct for builtins
 * @name: Name of builtin
 * @func: Function pointer to builtin
 */
typedef struct builtin_t
{
	char *name;
	void (*func)(char **args);
} builtin_t;

/**
 * struct shell_op - Struct for operators
 * @op: shell_op
 * @len: Length of s_op
 */
typedef struct shell_op
{
	char *op;
	int len;
} shell_op;

extern shell_op operators[];

#define OPERATORS_SIZE 4

/* main_r.c*/
int run_from_file(char *argv[]);
int run_non_interactive(char *argv[]);
int run_interactive(char *p_name);

/* main_u.c */
ssize_t get_input(char **line, int fd);
int handle_eof_empty(char *line, ssize_t size);
void free_main(char **args, char *expression, char *command);
int handle_operator(int code, shell_op *s_op, shell_op operators[]);

/* parser.c */
size_t parse_args(char ***args, char *line, size_t size, const char *delims);
int parse_and_execute(char *p_name, char **args, char *expression);

/* command0.c */
char *get_command(char *arg);
int execute_command(char *command, char **args);

/* command_utils1.c */
char *_getenv(const char *name);
char *get_stat(char *filename);
char *append_slash(char *filename);
char *get_file_path(char *directory, char *filename);

/* getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);

/* string_1.c*/
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, char *src, int n);

/* string2.c */
char *_strpbrk(const char *s, const char *accept);
char *_strchr(const char *s, int c);
char *_strtok(char *str, const char *delim);

/* string3.c */
size_t _strlen(const char *str);
char *_strstr(char *haystack, char *needle);
int _isspace(char c);
int _atoi(char *s);
void *_realloc(void *ptr, size_t size);

/* built.c */
int execute_builtin(char **args);
void handle_exit(char **args);
void handle_env(char **args);
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_cd(char **args);
void set_args(char *oldpwd, char *newpwd);

/* operat.c */
char *get_line(char **line, shell_op **op, shell_op operators[]);
shell_op *get_operator(char *line, int *len, shell_op operators[]);

#endif
