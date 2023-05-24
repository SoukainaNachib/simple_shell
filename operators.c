#include "shell.h"

/**
 * get_line - Get line
 * @line: Line
 * @op: shell_op
 * @operators: Operators
 *
 * Return: Pointer to line
 */
char *get_line(char **line, shell_op **op, shell_op operators[])
{
	char *command, *last_command;
	int len = -1, op_len = 0, last_len;
	shell_op *s_op = get_operator(*line, &len, operators);

	if (s_op)
	{
		op_len = s_op->len;
		command = malloc(len + 1);
		if (!command)
		{
			perror("memory");
			return (NULL);
		}
		_strncpy(command, *line, len);
		command[len] = '\0';
		*line += len + op_len;
		*op = s_op;
		return (command);
	}

	last_len = _strlen(*line);
	last_command = malloc(last_len + 1);
	if (!last_command)
	{
		perror("memory");
		return (NULL);
	}
	_strcpy(last_command, *line);
	last_command[last_len] = '\0';
	*line = '\0';
	return (last_command);
}

/**
 * get_operator - Get s_op
 * @line: Line
 * @len: Length
 * @operators: Operators
 *
 * Return: Pointer to s_op
 */
shell_op *get_operator(char *line, int *len, shell_op operators[])
{
	shell_op *op = NULL;
	char *ptr;
	int pos, i;

	for (i = 0; i < OPERATORS_SIZE; i++)
	{
		ptr = _strstr(line, operators[i].op);
		if (!ptr)
			continue;

		pos = ptr - line;
		if (*len == -1 || *len > pos)
		{
			*len = pos;
			op = &operators[i];
		}
	}

	return (op);
}
