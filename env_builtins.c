#include "shell.h"

/**
 * handle_env - Print environment variables
 * @args: Arguments
 */
void handle_env(char **args)
{
	char **env = environ;
	(void)args;

	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * copy_environment - Copy environment variables
 * @env_copy: Pointer to environment copy
 * @num_env_vars: Pointer to number of environment variables
 */
void copy_environment(char ***env_copy, int *num_env_vars)
{
	int i;

	while (environ[*num_env_vars])
		(*num_env_vars)++;

	*env_copy = malloc((*num_env_vars + 2) * sizeof(char *));

	for (i = 0; i < *num_env_vars; i++)
		(*env_copy)[i] = _strdup(environ[i]);

	(*env_copy)[*num_env_vars] = NULL;
}

/**
 * concat_env_string - Concatenate environment string
 * @new_env: Pointer to new environment string
 * @arg1: First argument
 * @arg2: Second argument
 */
void concat_env_string(char *new_env, char *arg1, char *arg2)
{
	_strcpy(new_env, arg1);
	_strcat(new_env, "=");
	_strcat(new_env, arg2);
}

/**
 * handle_setenv - Set environment variable
 * @args: Arguments
 */
void handle_setenv(char **args)
{
	char **env_copy;
	char *variable, *value, *new_env;
	int i, num_env_vars = 0;

	if (!args[1] || !args[2])
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		return;
	}
	copy_environment(&env_copy, &num_env_vars);
	for (i = 0; env_copy[i]; i++)
	{
		variable = _strdup(env_copy[i]);
		value = _strchr(variable, '=');
		if (value)
		{
			*value = '\0';
			value++;
			if (_strcmp(variable, args[1]) == 0)
			{
				new_env = malloc(_strlen(args[1]) + _strlen(args[2]) + 2);
				concat_env_string(new_env, args[1], args[2]);
				free(env_copy[i]);
				env_copy[i] = new_env;
				environ = env_copy;
				free(variable);
				variable = NULL;
				return;
			}
		}
		free(variable);
		variable = NULL;
	}
	new_env = malloc(_strlen(args[1]) + _strlen(args[2]) + 2);
	concat_env_string(new_env, args[1], args[2]);
	env_copy = _realloc(env_copy, (num_env_vars + 3) * sizeof(char *));
	env_copy[num_env_vars] = new_env;
	env_copy[num_env_vars + 1] = NULL;
	env_copy[num_env_vars + 2] = NULL;
	environ = env_copy;
}

/**
 * handle_unsetenv - Unset environment variable
 * @args: Arguments
 */
void handle_unsetenv(char **args)
{
	char **env_copy;
	char *variable, *value;
	int i, j, num_env_vars = 0, found = 0;

	if (!args[1])
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return;
	}
	copy_environment(&env_copy, &num_env_vars);
	for (i = 0; env_copy[i]; i++)
	{
		variable = _strdup(env_copy[i]);
		value = _strchr(variable, '=');
		if (value)
		{
			*value = '\0';
			value++;
			if (_strcmp(variable, args[1]) == 0)
			{
				free(env_copy[i]);
				/* Shift remaining variables to fill the gap */
				for (j = i; env_copy[j]; j++)
					env_copy[j] = env_copy[j + 1];
				found = 1;
				free(variable);
				variable = NULL;
				break;
			}
		}
		free(variable);
		variable = NULL;
	}
	if (!found)
	{
		write(STDERR_FILENO, "Variable not found: ", 20);
		write(STDERR_FILENO, args[1], strlen(args[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	environ = env_copy;
}
