#include "shell.h"

/**
 * _strcpy - Copies a string
 * @d: the Destination
 * @s: the Source
 * Return: pointer to destination
 */
char *_strcpy(char *d, char *s)
{
	int a = 0;

	if (d == s || s == 0)
		return (d);
	while (s[a])
	{
		d[a] = s[a];
		a++;
	}
	d[a] = 0;
	return (d);
}

/**
 * _strdup - Duplicates a String
 * @s: the String to Duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *k;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	k = malloc(sizeof(char) * (len + 1));
	if (!k)
		return (NULL);
	for (len++; len--;)
		k[len] = *--s;
	return (k);
}

/**
 *_puts - Prints an Input String
 *@s: the String to be Printed
 * Return: Nothing
 */
void _puts(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_putchar(s[a]);
		a++;
	}
}

/**
 * _putchar - Writes the Character to Stdout
 * @c: The character to print
 * Return: On success 1.
 */
int _putchar(char c)
{
	static int a;
	static char buffr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buffr, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buffr[a++] = c;
	return (1);
}
