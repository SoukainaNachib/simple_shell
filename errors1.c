#include "shell.h"

/**
 * _erratoi - Converts a Str to an Int
 * @m: The str to be converted
 * Return: 0 if not Str, Converted Num Otherwise
 *       -1 On Error
 */
int _erratoi(char *m)
{
	int k = 0;
	unsigned long int result = 0;

	if (*m == '+')
		m++;  /* TODO: why does this make main return 255? */
	for (k = 0;  m[k] != '\0'; k++)
	{
		if (m[k] >= '0' && m[k] <= '9')
		{
			result *= 10;
			result += (m[k] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints an Error MSG
 * @inf: The parameter & Return Info Struct
 * @estr: Str Containing Specified Error Type
 * Return: 0 if no Num in Str, Converted Num Otherwise
 *        -1 on Error
 */
void print_error(info_t *inf, char *estr)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Function Prints a Decimal (int) Num (base 10)
 * @input: The Input
 * @f: the Filedescriptor to Write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int f)
{
	int (*__putchar)(char) = _putchar;
	int k, count = 0;
	unsigned int _abs_, current;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + current / k);
			count++;
		}
		current %= k;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converter Function, a Clone of Itoa
 * @N: Num
 * @base: base
 * @flags: Arg flags
 *
 * Return: Str
 */
char *convert_number(long int N, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = N;

	if (!(flags & CONVERT_UNSIGNED) && N < 0)
	{
		n = -N;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Function Replaces First Instance of '#' with '\0'
 * @buf: Address of the Str to modify
 *
 * Return: Always return 0;
 */
void remove_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
