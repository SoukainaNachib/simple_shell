#include "shell.h"

/**
 * _strpbrk - Searches a string for any set of a set of bytes.
 * @s: The string to check.
 * @accept: The bytes to match.
 *
 * Return: Returns a pointer to the byte in s
 * that matches one of the bytes in accept,
 * or NULL if no such byte is found
 */
char *_strpbrk(const char *s, const char *accept)
{
	int i, j;

	for (i = 0; s[i]; i++)
		for (j = 0; accept[j]; j++)
			if (s[i] == accept[j])
				return ((char *)(s + i));

	return (NULL);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @str: The string to search in.
 * @c: The character to locate.
 *
 * Return: Returns a pointer to the first occurrence of the character c
 *			in the string str, or NULL if the character is not found.
 */

char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		++str;
	}

	return (NULL);
}

/**
 * _strtok - Breaks a string into a sequence of
 * zero or more nonempty tokens
 * @str: The string to tokenize
 * @delim: The string of the delimiter characters
 *
 * Return: A pointer to the next token,
 * or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *ptr;
	char *token;

	if (str)
		ptr = str;

	else if (!ptr || !delim || !*delim)
		return (NULL);

	while (*ptr && _strchr(delim, *ptr))
		ptr++;

	if (!*ptr)
		return (NULL);

	token = ptr;
	while (*ptr && !_strchr(delim, *ptr))
		ptr++;

	if (*ptr)
		*ptr++ = '\0';
	else
		ptr = NULL;

	return (token);
}
