#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
