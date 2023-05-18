#include "shell.h"

/**
 * bfree - Frees a Pointer And NULLs The Address
 * @ptr: Address of The Pointer To Free
 *
 * Return: 1 if Freed, Otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
