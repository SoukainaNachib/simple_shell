#include "shell.h"

/**
 * interactive - Returns True if Shell is interactive Mode
 * @inf: Structure Adress
 *
 * Return: 1 interctive mode, 0 other
 */

int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 *_isalpha - checks for Alpha Char
 *@c: The Char to input
 *Return: 1 if c is Alpha, 0 other
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - checks if Char is a delimeter
 * @c: the Char to check
 * @delim: the delimeter of String
 * Return: 1 if True, 0 if False
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_atoi - converts a String to an int
 *@s: the String to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

