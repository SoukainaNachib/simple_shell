#include "shell.h"

/**
 * without_comment - Deletes Comments From The Input
 *
 * @in: Input String
 * Return: Input Without Comments
 */
char *without_comment(char *in)
{
	int k, up_to;

	up_to = 0;
	for (k = 0; in[k]; k++)
	{
		if (in[k] == '#')
		{
			if (k == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[k - 1] == ' ' || in[k - 1] == '\t' || in[k - 1] == ';')
				up_to = k;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, k, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - LOOP of Shell
 * @datash: Data Relevant (av, input, args)
 *
 * Return: No Return.
 */
void shell_loop(data_shell *datash)
{
	int loop, k_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&k_eof);
		if (k_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
