#include "shell.h"

/**
 *_memset - Fills Memory With a Constant Byte
 *@str: The Pointer to the Memory Area
 *@c: the byte to Fill *str With
 *@n: the amount of Bytes to be Filled
 *Return: a pointer to the memory area str
 */
char *_memset(char *str, char c, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		str[a] = c;
	return (str);
}

/**
 * ffree - Frees a String of Strings
 * @ptr: string of Strings
 */
void ffree(char **ptr)
{
	char **l = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(l);
}

/**
 * _realloc - Reallocates a Block of Memory
 * @ptr: Pointer to Previous Malloc'ated Block
 * @o_size: Byte Size of Previous Block
 * @n_size: Byte Size of New Block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *str;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == o_size)
		return (ptr);

	str = malloc(n_size);
	if (!str)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		str[o_size] = ((char *)ptr)[o_size];
	free(ptr);
	return (str);
}
