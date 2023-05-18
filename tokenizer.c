#include "shell.h"

/**
 * **strtow - Splits a Str into Words. Repeat Delimiters Are Ignored
 * @str: The input Str
 * @dlm: The Delimeter Str
 * Return: a Pointer to an [] of Str, or NULL on Failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numw++;

	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numw; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - Splits a String Into Words
 * @str: The Input String
 * @dlm: The Delimeter
 * Return: a pointer to an [] of Str, or NULL on Failure
 */
char **strtow2(char *str, char dlm)
{
	int i, j, k, m, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != dlm && str[i + 1] == dlm) ||
		    (str[i] != dlm && !str[i + 1]) || str[i + 1] == dlm)
			numw++;
	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numw; j++)
	{
		while (str[i] == dlm && str[i] != dlm)
			i++;
		k = 0;
		while (str[i + k] != dlm && str[i + k] && str[i + k] != dlm)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
