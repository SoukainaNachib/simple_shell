#include "shell.h"

/**
 * main - Entry point
 * @arc: num of arg
 * @arv: array of arg
 *
 * Return: 0 or 1
 */

int main(int arc, char *arv[])
{
	int is_pipline = 1;

	if (arc > 1)
		run_from_file(arv);

	while (true)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, PROMPT, 2);
			run_interactive(arv[0]);
			is_pipline = 0;
		}

		if (is_pipline)
		{
			run_non_interactive(arv);
			break;
		}
	}

	return (0);
}
