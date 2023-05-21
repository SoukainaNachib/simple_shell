#include "shell.h"

/**
 * input_buf - Buffers Chained Commands
 * @m: Parameter struct
 * @m: Address of buffer
 * @l: Address of len var
 * Return:Number of  bytes read
 */
ssize_t input_buf(info_t *m, char **n, size_t *l)
{
	ssize_t a = 0;
	size_t k = 0;

	if (!*l)
	{
		free(*n);
		*n = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(n, &k, stdin);
#else
		a = _getline(m, n, &k);
#endif
		if (a > 0)
		{
			if ((*n)[a - 1] == '\n')
			{
				(*n)[a - 1] = '\0';
				a--;
			}
			m->linecount_flag = 1;
			remove_comments(*n);
			build_history_list(m, *n, m->histcount++);
			{
				*l = a;
				m->cmd_buf = n;
			}
		}
	}
	return (a);
}

/**
 * get_input - Gets a Line minus the newline
 * @m: Parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *m)
{
	static char *buffr;
	static size_t a, b, len;
	ssize_t c = 0;
	char **buf = &(m->arg), *k;

	_putchar(BUF_FLUSH);
	c = input_buf(m, &buffr, &len);
	if (c == -1)
		return (-1);
	if (len)
	{
		b = a;
		k = buffr + a;

		check_chain(m, buffr, &b, a, len);
		while (b < len)
		{
			if (is_chain(m, buffr, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			m->cmd_buf_type = CMD_NORM;
		}

		*buf = k; 
		return (_strlen(k));
	}

	*buf = buffr;
	return (c);
}

/**
 * read_buf - Reads a buffer
 * @m: Parameter struct
 * @n: Buffer
 * @l: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *m, char *n, size_t *l)
{
	ssize_t c = 0;

	if (*l)
		return (0);
	c = read(m->readfd, n, READ_BUF_SIZE);
	if (c >= 0)
		*l = c;
	return (c);
}

/**
 * _getline - Gets the Next Line of Input From STDIN
 * @m: Parameter Struct
 * @ptr: Address of Pointer to buffer
 * @lent: Size of Preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *m, char **ptr, size_t *lent)
{
	static char buffr[READ_BUF_SIZE];
	static size_t a, l;
	size_t k;
	ssize_t c = 0, b = 0;
	char *str = NULL, *n = NULL, *p;

	str = *ptr;
	if (str && lent)
		b = *lent;
	if (a == l)
		a = l = 0;

	c = read_buf(m, buffr, &l);
	if (c == -1 || (c == 0 && l == 0))
		return (-1);

	p = _strchr(buffr + a, '\n');
	k = p ? 1 + (unsigned int)(p - buffr) : l;
	n = _realloc(str, b, b ? b + k : k + 1);
	if (!n)
		return (str ? free(str), -1 : -1);

	if (b)
		_strncat(n, buffr + a, k - a);
	else
		_strncpy(n, buffr + a, k - a + 1);

	b += k - a;
	a = k;
	str = n;

	if (lent)
		*lent = b;
	*ptr = str;
	return (b);
}

/**
 * sigintHandler - blocks ctrl-C
 * @s_num: the signal number
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int s_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
