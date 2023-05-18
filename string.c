#include "shell.h"

/**
 * _strlen - Returns The Length Of a Str
 * @m: The Str Whose Length to Check
 *
 * Return: Int length of Str
 */
int _strlen(char *m)
{
	int k = 0;

	if (!m)
		return (0);

	while (*m++)
		k++;
	return (k);
}

/**
 * _strcmp - Performs lexicogarphic Comparison of 2 Strangs.
 * @s1: The 1 strang
 * @s2: The 2 strang
 *
 * Return: - s1 < s2, + s1 > s2, 0 s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if Needle Starts With Haystack
 * @haystack: Str to Search
 * @needle: The Substring to Find
 *
 * Return: Address of Next Char of Haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates 2 str
 * @dest: The Destination Buffer
 * @sr: The Source Buffer
 *
 * Return: Pointer to Destination Buffer
 */
char *_strcat(char *dest, char *sr)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*sr)
		*dest++ = *sr++;
	*dest = *sr;
	return (ret);
}
