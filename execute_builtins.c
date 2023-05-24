#include "shell.h"

/**
 * execute_builtin - Execute builtin
 * @args: Arguments
 *
 * Return: Status
 */
int execute_builtin(char **args)
{
	size_t i;
	builtin_t builtins[] = {
		{"exit", handle_exit},
		{"env", handle_env},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"cd", handle_cd}
	};
	size_t size = sizeof(builtins) / sizeof(builtin_t);

	for (i = 0; i < size; i++)
		if (_strcmp(args[0], builtins[i].name) == 0)
		{
			builtins[i].func(args);
			return (0);
		}

	return (1);
}
