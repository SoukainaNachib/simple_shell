#define _SHELL_H_
#ifdef _SHELL_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*FOR COMMAND CHANGING AND CONVERT_NUMBER*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*for WRITE/RED BUFFERS  */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 IF USING SYSTEM GETLINE()*/
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * structure liststr - Singly Linked List
 * @N: Number field
 * @str: string
 * @next: point to the next node
 * */
typedef struct liststr
{
	int N;
	char *str;
	struct liststr *next;
} list_t;

/**
 * Struct passinfo - contains Pseudo-Arguements
 * @arg: A string generated from getline containing arguements
 * @argv: An array of strings generated from arg
 * @Argc: the argument count
 * @path: A string path for the current command
 * @fname: The program filename
 * @env: Linked list local copy of environ
 * @environ: Custom modified copy of environ from LL env
 * @line_count: The error count
 * @err_num: The error code for exit()s
 * @linecount_flag: If on count this line of input
 * @history: the history node
 * @alias: The alias node
 * @env_changed: On if environ was changed
 * @status: The return status of the last exec'd command
 * @histcount: The history line number count
 * @cmd_buf: Address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The fd from which to read line input
 */

typedef struct passinfo
{
	char *path;
	char *arg;
	char **argv;
	int argc;
	int err_num;
	unsigned int line_count;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int status;
	int env_changed;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 *struct builtin - contains a builtin string and the function
 *@type: The builtin command flag
 *@function: The function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/*Toem_parser.c */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);

/*Toem_shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/*Toem_errors.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

/*Toem_errors1.c */
void remove_comments(char *);
int print_d(int, int);
void print_error(info_t *, char *);
int _erratoi(char *);
char *convert_number(long int, int, int);

/*Loophsh.c */
int loophsh(char **);

/*Toem_string.c */
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);

/*Toem_string1.c */
char *_strdup(const char *);
char *_strcpy(char *, char *);
int _putchar(char);
void _puts(char *);

/*Toem_exits.c */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/*Toem_realloc.c */
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);

/*Toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/*Toem_builtin.c */
int _myhelp(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);

/*Toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*Toem_getinfo.c */
void free_info(info_t *, int);
void clear_info(info_t *);
void set_info(info_t *, char **);

/*Toem_getline.c */
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/*Toem_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/*Toem_environ.c */
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _myenv(info_t *);
char *_getenv(info_t *, const char *);

/*Toem_lists.c */
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, char *, int);
list_t *add_node_end(list_t **, char *, int);
size_t print_list_str(const list_t *);

/*Toem_lists1.c */
char **list_to_strings(list_t *);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*Toem_history.c */
int write_history(info_t *info);
char *get_history_file(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

/*Toem_vars.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_chain(info_t *, char *, size_t *);

/* Toem_atoi.c */
int _isalpha(int);
int interactive(info_t *);
int is_delim(char, char *);
int _atoi(char *);

#endif
