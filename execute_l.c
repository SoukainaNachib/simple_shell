#include "shell.h"

/**
 * exec_line - Finds Builtins And Commands
 *
 * @datash: Data Relevant (args)
 * Return: 1 On Success.
 */

int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
