#include "shell.h"

/**
 **_strncpy - Copies a Str
 *@dest: The Destination Str To Be Copied To
 *@src: The Source Str
 *@N: The Amount Of Char To Be Copied
 *Return: The Concatenated Str
 */
char *_strncpy(char *dest, char *src, int N)
{
	int k, j;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < N - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < N)
	{
		j = k;
		while (j < N)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates 2 Str
 *@dest: The First Str
 *@src: The Second Str
 *@N: The Amount Of Bytes To Be Maximally used
 *Return: The Concatenated Str
 */
char *_strncat(char *dest, char *src, int N)
{
	int k, j;
	char *s = dest;

	k = 0;
	j = 0;
	while (dest[k] != '\0')
		k++;
	while (src[j] != '\0' && j < N)
	{
		dest[k] = src[j];
		k++;
		j++;
	}
	if (j < N)
		dest[k] = '\0';
	return (s);
}
/**
 **_strchr - Locates a Char in a Str
 *@s: The Str to be Parsed
 *@c: The chara To Look For
 *Return: (s) a Pointer To The Memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
