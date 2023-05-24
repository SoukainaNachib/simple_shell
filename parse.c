#include "shell.h"

/**
 * parse_args - Parse arguments
 * @args: Array of arguments
 * @line: Line
 * @size: Size
 * @delims: Delimiters
 *
 * Return: 0 or 1
 */
size_t parse_args(char ***args, char *line, size_t size, const char *delims)
{
	char *token;
	size_t len = size / 2 + size % 2 + 1;
	size_t i, j;

	*args = malloc(len * sizeof(char *));
	if (!*args)
		return (1);

	token = _strtok(line, delims);
	for (i = 0; token; i++)
	{
		(*args)[i] = malloc((_strlen(token) + 1) * sizeof(char));
		if (!(*args)[i])
		{
			for (j = 0; j < i; j++)
			{
				free((*args)[j]);
				(*args)[j] = NULL;
			}
			free(*args);
			*args = NULL;
			return (0);
		}

		_strcpy((*args)[i], token);
		token = _strtok(NULL, delims);
	}

	(*args)[i] = NULL;
	return (1);
}

/**
 * parse_and_execute - Parse and execute command
 * @p_name: Program name
 * @args: Array of arguments
 * @expression: Expression
 *
 * Return: 0 or 1
 */
int parse_and_execute(char *p_name, char **args, char *expression)
{
	char *command = NULL;
	int code;

	parse_args(&args, expression, _strlen(expression), DELIMITERS);
	if (execute_builtin(args) == 0)
		return (1);

	command = get_command(args[0]);
	if (!command)
	{
		perror(p_name);
		return (1);
	}

	code = execute_command(command, args);

	return (code);
}
