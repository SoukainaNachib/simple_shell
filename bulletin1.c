#include "shell.h"

/**
 * _myhistory - Displays the History List
 * @f: Structure Containing Potential Arguments.
 *  Return:0
 */
int _myhistory(info_t *f)
{
	print_list(f->history);
	return (0);
}

/**
 * unset_alias - Sets Alias to String
 * @m: Parameter Struct
 * @n: the String Alias
 *
 * Return:0 on success, 1 on error
 */
int unset_alias(info_t *m, char *n)
{
	char *ptr, i;
	int r;

	ptr = _strchr(n, '=');
	if (!ptr)
		return (1);
	i = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(m->alias),
		get_node_index(m->alias, node_starts_with(m->alias, n, -1)));
	*ptr = i;
	return (r);
}

/**
 * set_alias - Sets Alias to String
 * @m: Parameter Struct
 * @n: the String Alias
 * Return:0 on success, 1 on error
 */
int set_alias(info_t *m, char *n)
{
	char *ptr;

	ptr = _strchr(n, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(m, n));

	unset_alias(m, n);
	return (add_node_end(&(m->alias), n, 0) == NULL);
}

/**
 * print_alias - Prints an Alias String
 * @n: the Alias Node
 * Return:0 on success, 1 on error
 */
int print_alias(list_t *n)
{
	char *ptr = NULL, *i = NULL;

	if (n)
	{
		ptr = _strchr(n->str, '=');
		for (i = n->str; i <= ptr; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the Alias Builtin
 * @m: Structure Containing Potential Arguments
 *  Return:0
 */
int _myalias(info_t *m)
{
	int a = 0;
	char *ptr = NULL;
	list_t *n = NULL;

	if (m->argc == 1)
	{
		n = m->alias;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (a = 1; m->argv[a]; a++)
	{
		ptr = _strchr(m->argv[a], '=');
		if (ptr)
			set_alias(m, m->argv[a]);
		else
			print_alias(node_starts_with(m->alias, m->argv[a], '='));
	}

	return (0);
}
