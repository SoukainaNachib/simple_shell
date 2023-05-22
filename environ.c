#include "shell.h"

/**
 * _myenv - prints the current environment
 * @m: Structure containing potential arguments.
 * Return:0
 */
int _myenv(info_t *m)
{
	print_list_str(m->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @m: Structure containing potential arguments.
 * @n: env var name
 * Return: the value
 */
char *_getenv(info_t *m, const char *n)
{
	list_t *list = m->env;
	char *ptr;

	while (list)
	{
		ptr = starts_with(list->str, n);
		if (ptr && *ptr)
			return (ptr);
		list = list->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable.
 * @m: Structure containing potential arguments.
 *  Return:0
 */
int _mysetenv(info_t *m)
{
	if (m->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(m, m->argv[1], m->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @m: Structure containing potential arguments.
 *  Return:0
 */
int _myunsetenv(info_t *m)
{
	int a;

	if (m->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	a = 1;
	while (a <= m->argc)
	{
		_unsetenv(m, m->argv[a]);
		a++;
	}

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @m: Structure containing potential arguments.
 * Return: 0
 */
int populate_env_list(info_t *m)
{
	list_t *list = NULL;
	size_t a;
	char **envirn = NULL;

	for (a = 0; envirn[a]; a++)
		add_node_end(&list, envirn[a], 0);
	m->env = list;
	return (0);
}
