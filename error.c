#include "shell.h"

/**
 * get_error - Calls The Error According The Builtin, SYntax or Permission
 * @dash: Data Structure That Contains Args
 * @eval: Error Value
 * Return: Error
 */
int get_error(data_shell *dash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(dash);
		break;
	case 126:
		error = error_path_126(dash);
		break;
	case 127:
		error = error_not_found(dash);
		break;
	case 2:
		if (_strcmp("exit", dash->args[0]) == 0)
			error = error_exit_shell(dash);
		else if (_strcmp("cd", dash->args[0]) == 0)
			error = error_get_cd(dash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	dash->status = eval;
	return (eval);
}
