#include "shell.h"

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: A negative value if s1 is less than s2.
 * A positive value if s1 is greater than s2.
 * 0, if the s1 and s2 are equal.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int len = 0;
	int i = 0;

	while (dest[len] != '\0')
		len++;

	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}

	dest[len + i] = src[i];

	return (dest);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: the string to copy.
 *
 * Return: pointer to the duplicate of str, otherwise NULL.
 */
char *_strdup(char *str)
{
	char *dupstr;
	int i;

	if (!str)
		return (NULL);

	dupstr = malloc(_strlen(str) + 1);
	if (!dupstr)
	{
		return (NULL);
	}

	for (i = 0; str[i]; i++)
		dupstr[i] = str[i];

	dupstr[i] = '\0';

	return (dupstr);
}

/**
 * *_strcpy - Copies string.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	char *d = dest;

	while (*src)
		*d++ = *src++;

	*d = '\0';

	return (dest);
}

/**
 * _strncpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The number of bytes to copy.
 *
 * Return: Pointer to the string dest.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
