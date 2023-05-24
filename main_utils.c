#include "shell.h"

/**
 * get_input - Get input from file descriptor
 * @line: Pointer to line
 * @fd: File descriptor
 *
 * Return: Number of bytes read
 */
ssize_t get_input(char **line, int fd)
{
	size_t n = 0;
	ssize_t read_bytes = 0;

	read_bytes = _getline(line, &n, fd);

	if (read_bytes == -1)
		return (-1);

	if (read_bytes == 0)
		return (-2);

	if ((*line)[read_bytes - 1] == '\n')
		(*line)[read_bytes - 1] = '\0';

	return (read_bytes);
}

/**
 * handle_eof_empty - Handle EOF and empty line
 * @line: Line
 * @size: Size
 *
 * Return: 0 or 1
 */
int handle_eof_empty(char *line, ssize_t size)
{
	if (size == -2)
		write(STDOUT_FILENO, "\n", 1);

	if (size == -1 || size == -2)
		exit(0);

	if (!*line)
		return (1);

	return (0);
}

/**
 * free_main - Free memory
 * @args: Arguments
 * @expression: Expression
 * @command: Command
 */
void free_main(char **args, char *expression, char *command)
{
	size_t i;

	if (args)
	{
		for (i = 0; args[i]; i++)
		{
			if (args[i] != command)
			{
				free(args[i]);
				args[i] = NULL;
			}
		}
		free(args);
		args = NULL;
	}
	if (expression)
	{
		free(expression);
		expression = NULL;
	}
	if (command)
	{
		free(command);
		command = NULL;
	}
}

/**
 * handle_operator - Handle s_op
 * @code: Exit code
 * @s_op: shell_op
 * @operators: Operators
 *
 * Return: 0 or 1
 */
int handle_operator(int code, shell_op *s_op, shell_op operators[])
{
	if (!s_op || !s_op->op)
		return (0);

	if (code != 0 && (_strcmp(s_op->op, operators[1].op) == 0))
		return (1);

	if (code == 0 && (_strcmp(s_op->op, operators[2].op) == 0))
		return (1);

	if (_strcmp(s_op->op, operators[3].op) == 0)
		return (1);

	return (0);
}
