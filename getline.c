#include "shell.h"

/**
 * _getline - Get line
 * @lineptr: Line pointer
 * @n: Size
 * @fd: File descriptor
 *
 * Return: Number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	ssize_t nread = 0;

	if (!lineptr || !n || fd < 0)
		return (-1);

	*lineptr = malloc(BUFFER_SIZE * sizeof(char));
	if (!*lineptr)
		return (-1);

	*n = BUFFER_SIZE;

	nread = read(fd, *lineptr, BUFFER_SIZE - 1);

	if (nread > 0)
		(*lineptr)[nread] = '\0';

	while (_isspace(**lineptr))
		(*lineptr)++;

	if (!*lineptr)
		return (-1);

	return (nread);
}
