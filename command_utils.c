#include "shell.h"

/**
 * _getenv - Get environment variable
 * @name: Name of environment variable
 *
 * Return: Pointer to environment variable
 */
char *_getenv(const char *name)
{
	char **env;
	char *tmp, *var, *value;
	char *result = NULL;

	if (!name || !*name)
		return (NULL);

	for (env = environ; *env; ++env)
	{
		tmp = _strdup(*env);
		if (!tmp)
			return (NULL);

		var = _strtok(tmp, "=");
		if (!var)
		{
			free(tmp);
			tmp = NULL;
			return (NULL);
		}

		if (_strcmp(var, name) == 0)
		{
			value = _strtok(NULL, "=");
			if (value)
				result = _strdup(value);

			free(tmp);
			tmp = NULL;
			return (result);
		}

		free(tmp);
		tmp = NULL;
	}

	return (NULL);
}

/**
 * get_stat - Get stat of file
 * @filename: Filename
 *
 * Return: Pointer to filename
 */
char *get_stat(char *filename)
{
	struct stat st;

	if (!filename)
	{
		perror("Filename");
		exit(1);
	}

	if (stat(filename, &st) == 0)
		if (access(filename, X_OK) == 0)
			return (filename);

	return (NULL);
}

/**
 * append_slash - Append slash to filename
 * @filename: Filename
 *
 * Return: Pointer to new filename
 */
char *append_slash(char *filename)
{
	char *new_filename = NULL;
	size_t length;

	if (!filename)
	{
		perror("Filename");
		exit(1);
	}

	length = _strlen(filename);
	new_filename = malloc(length + 2);
	if (!new_filename)
	{
		perror("Failed to allocate memory");
		exit(1);
	}

	new_filename[0] = '/';
	new_filename[1] = '\0';
	_strcat(new_filename, filename);

	return (new_filename);
}

/**
 * get_file_path - Get file path
 * @directory: Directory
 * @filename: Filename
 *
 * Return: Pointer to file path
 */
char *get_file_path(char *directory, char *filename)
{
	char *file_path;

	if (!directory || !filename)
	{
		perror("Error");
		exit(1);
	}

	file_path = malloc(_strlen(directory) + _strlen(filename) + 1);
	if (!file_path)
	{
		perror("Failed to allocate memory");
		exit(1);
	}

	file_path[0] = '\0';
	_strcat(file_path, directory);
	_strcat(file_path, filename);

	return (file_path);
}
