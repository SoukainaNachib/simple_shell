#include "shell.h"

/**
 * get_command - Get command
 * @arg: Argument
 *
 * Return: Command
 */
char *get_command(char *arg)
{
	char *path, *filename = NULL, *directory = NULL, *file_path = NULL;

	if (get_stat(arg))
		return (arg);

	path = _strdup(_getenv("PATH"));
	if (!path)
	{
		perror("Failed to get PATH");
		return (NULL);
	}
	filename = append_slash(arg);
	directory = _strtok(path, ":");
	while (directory)
	{
		file_path = get_file_path(directory, filename);

		if (get_stat(file_path))
		{
			free(filename);
			free(path);
			filename = NULL;
			path = NULL;
			return (file_path);
		}

		free(file_path);
		file_path = NULL;
		directory = _strtok(NULL, ":");
	}

	free(filename);
	free(directory);
	free(file_path);
	free(path);
	filename = NULL;
	directory = NULL;
	file_path = NULL;
	path = NULL;
	return (NULL);
}

/**
 * execute_command - Execute command
 * @command: Command
 * @args: Arguments
 *
 * Return: Status
 */
int execute_command(char *command, char **args)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (1);
	}

	if (child == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
		wait(&status);

	return (status);
}
