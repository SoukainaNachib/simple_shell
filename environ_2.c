#include "shell.h"

/**
 * copy_info -Ccopies Info to Create
 * a New Env or Alias
 * @name: Name (env or alias)
 * @value: Value (env or alias)
 *
 * Return: New Env or Alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - Sets An Envirenement Var
 *
 * @name: Name of The Environment var
 * @value: Value Of The Environment Var
 * @datash: Data Structure
 * Return: No return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int k;
	char *var_env, *name_env;

	for (k = 0; datash->_environ[k]; k++)
	{
		var_env = _strdup(datash->_environ[k]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[k]);
			datash->_environ[k] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, k, sizeof(char *) * (k + 2));
	datash->_environ[k] = copy_info(name, value);
	datash->_environ[k + 1] = NULL;
}

/**
 * _setenv - Compares Env Var Names
 * With The Name Passed.
 * @datash: Data Relevant (env name and env value)
 *
 * Return: 1 On Success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - Deletes a Environment Var
 *
 * @datash: Data Relevant
 *
 * Return: 1 On Success.
 */

int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int m, d, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (m = 0; datash->_environ[m]; m++)
	{
		var_env = _strdup(datash->_environ[m]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = m;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (m));
	for (m = d = 0; datash->_environ[m]; m++)
	{
		if (m != k)
		{
			realloc_environ[d] = datash->_environ[m];
			d++;
		}
	}
	realloc_environ[d] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
