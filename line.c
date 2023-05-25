#include "shell.h"

/**
 * read_line - Reads The INput Str.
 *
 * @i_eof: Return Value Of GetLine Function
 * Return: Input Str
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
