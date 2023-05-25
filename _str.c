#include "shell.h"

/**
 * _strcat - Concatenate two strings
 * @dest: Char pointer the dest of the copied str
 * @src: Const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int k;
	int l;

	for (k = 0; dest[k] != '\0'; k++)
		;

	for (l = 0; src[l] != '\0'; l++)
	{
		dest[k] = src[l];
		k++;
	}

	dest[k] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t k;

	for (k = 0; src[k] != '\0'; k++)
	{
		dest[k] = src[k];
	}
	dest[k] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int k;

	for (k = 0; s1[k] == s2[k] && s1[k]; k++)
		;

	if (s1[k] > s2[k])
		return (1);
	if (s1[k] < s2[k])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int k = 0;

	for (; *(s + k) != '\0'; k++)
		if (*(s + k) == c)
			return (s + k);
	if (*(s + k) == c)
		return (s + k);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int k, l, bool;

	for (k = 0; *(s + k) != '\0'; k++)
	{
		bool = 1;
		for (l = 0; *(accept + l) != '\0'; l++)
		{
			if (*(s + k) == *(accept + l))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (k);
}
