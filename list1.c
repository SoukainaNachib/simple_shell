#include "shell.h"

/**
 * list_len - Determines Length of Linked list
 * @lst: Pointer to First node
 * Return: Size of List
 */
size_t list_len(const list_t *lst)
{
	size_t a = 0;

	while (lst)
	{
		lst = lst->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - Returns an Array of Strings of the list
 * @lst: Pointer to First Node
 * Return: Array of Strings
 */
char **list_to_strings(list_t *lst)
{
	list_t *n = lst;
	size_t a = list_len(lst), j;
	char **ptr;
	char *str;

	if (!lst || !a)
		return (NULL);
	ptr = malloc(sizeof(char *) * (a + 1));
	if (!ptr)
		return (NULL);
	for (a = 0; n; n = n->next, a++)
	{
		str = malloc(_strlen(n->str) + 1);
		if (!str)
		{
			for (j = 0; j < a; j++)
				free(ptr[j]);
			free(ptr);
			return (NULL);
		}

		str = _strcpy(str, n->str);
		ptr[a] = str;
	}
	ptr[a] = NULL;
	return (ptr);
}


/**
 * print_list - Prints All Elements of Linked list
 * @N: Pointer to First Node
 * Return: Size of List
 */
size_t print_list(const list_t *p)
{
	size_t a = 0;

	while (p)
	{
		_puts(convert_number(p->N, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - Returns Node Whose String Starts With Prefix
 * @n: Pointer to List Head
 * @p: String to Match
 * @c: the Next Character After Prefix to Match
 * Return: Match Node or Null
 */
list_t *node_starts_with(list_t *n, char *p, char c)
{
	char *ptr = NULL;

	while (n)
	{
		ptr = starts_with(n->str, p);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the Index of a Node
 * @h: Pointer to List Head
 * @n: Pointer to the Node
 * Return: Index of Node or -1
 */
ssize_t get_node_index(list_t *h, list_t *n)
{
	size_t a = 0;

	while (h)
	{
		if (h == n)
			return (a);
		h = h->next;
		a++;
	}
	return (-1);
}
