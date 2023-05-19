#include "shell.h"

/**
 *_eputs - Prints an Input String
 * @str: The String to be Printed
 * Return: Nothing
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - Writes the Character m to Stderr
 * @m: The Character to Print
 * Return: On success 1.
 */
int _eputchar(char m)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (m != BUF_FLUSH)
		buff[a++] = m;
	return (1);
}

/**
 * _putfd - Writes the Character m to given fd
 * @m: The Character to print
 * @fd: The Filedescriptor
 * Return: On success 1.
 */
int _putfd(char m, int fd)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buff, a);
		a = 0;
	}
	if (m != BUF_FLUSH)
		buff[a++] = m;
	return (1);
}

/**
 *_putsfd - Prints an Input String
 * @str: the String to be Printed
 * @fd: the Filedescriptor to Write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
