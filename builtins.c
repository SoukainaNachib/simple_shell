#include "shell.h"

/**
 * handle_exit - Exit shell
 * @args: Arguments
 */
void handle_exit(char **args)
{
	int code = 0;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
			code = _atoi(args[1]);

		free_main(args, NULL, NULL);
		exit(code);
	}
}

/**
 * handle_cd - Change directory
 * @args: Arguments
 */
void handle_cd(char **args)
{
	char *path = args[1];
	char *home_dir = _getenv("HOME");
	char *oldpwd = _getenv("PWD");
	char *newpwd;

	if (!path)
	{
		if (home_dir)
			path = home_dir;
		else
		{
			write(STDERR_FILENO, "HOME environment variable not set\n", 34);
			return;
		}
	}
	else if (_strcmp(path, "-") == 0)
	{
		path = _getenv("OLDPWD");
		if (!path)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return;
		}
		write(STDOUT_FILENO, path, _strlen(path));
		write(STDOUT_FILENO, "\n", 1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return;
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd");
		return;
	}
	set_args(oldpwd, newpwd);
	free(newpwd);
	newpwd = NULL;
}

/**
 * set_args - Set arguments for setenv
 * @oldpwd: Old working directory
 * @newpwd: New working directory
 */
void set_args(char *oldpwd, char *newpwd)
{
	char *args1[4], *args2[4];

	args1[0] = "setenv";
	args1[1] = "OLDPWD";
	args1[2] = oldpwd;
	args1[3] = NULL;
	handle_setenv(args1);

	args2[0] = "setenv";
	args2[1] = "PWD";
	args2[2] = newpwd;
	args2[3] = NULL;
	handle_setenv(args2);
}
