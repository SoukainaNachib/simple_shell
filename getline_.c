#include "shell.h"

/**
 * bring_line - Assigns The Line Var For Getline
 * @lineptr: Buffer That Store The Input Str
 * @buffer: Str That Is Been Called To Line
 * @n: Size Of Line
 * @j: Size Of Buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @lineptr: Buffer That Stores The Input
 * @n: Size Of Lineptr
 * @stream: Stream To Read From
 * Return: The Num of Bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int k;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		k = read(STDIN_FILENO, &t, 1);
		if (k == -1 || (k == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (k == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (k != 0)
		input = 0;
	return (retval);
}
