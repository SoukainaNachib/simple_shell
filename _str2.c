#include "shell.h"

/**
 * rev_string - Reverses a string.
 * @s: Input string.
 * Return: nothing
 */
void rev_string(char *s)
{
	int count = 0, k, l;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (k = 0; k < (count - 1); k++)
	{
		for (l = k + 1; l > 0; l--)
		{
			temp = *(str + l);
			*(str + l) = *(str + (l - 1));
			*(str + (l - 1)) = temp;
		}
	}
}
