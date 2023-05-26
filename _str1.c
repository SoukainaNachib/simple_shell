#include "shell.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 * Return: 1
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int m, n, k;

	for (m = 0, k = 0; str[m]; m++)
	{
		for (n = 0; delim[n]; n++)
		{
			if (str[n] == delim[n])
			{
				k++;
				break;
			}
		}
	}
	if (m == k)
		return (1);
	return (0);
}

/**
 * _strtok - Splits a string by some delimiter.
 * @str: Input string.
 * @delim: Delimiter.
 * Return: String splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int k, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		k = _strlen(str);
		str_end = &str[k];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (k = 0; delim[k]; k++)
		{
			if (*splitted == delim[k])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - defines if string passed is a number
 * @s: input string
 * Return: 1
 */
int _isdigit(const char *s)
{
	unsigned int k;

	for (k = 0; s[k]; k++)
	{
		if (s[k] < 48 || s[k] > 57)
			return (0);
	}
	return (1);
}
