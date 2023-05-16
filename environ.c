#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Return:0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *list = info->env;
	char *ptr;

	while (list)
	{
		ptr = starts_with(list->str, name);
		if (ptr && *ptr)
			return (ptr);
		list = list->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 *  Return:0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return:0
 */
int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	a = 1;
       while (a <= info->argc)
       {
		_unsetenv(info, info->argv[a]);
		a++;
       }

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *list = NULL;
	size_t a;

	a = 0;
       while (environ[a])
       {
		add_node_end(&list, environ[a], 0);
		a++;
       }
	info->env = list;
	return (0);
}
