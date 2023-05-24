#include "shell.h"

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 or 1
 */
int main(int argc, char *argv[])
{
	int is_pipline = 1;

	if (argc > 1)
		run_from_file(argv);

	while (true)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, PROMPT, 2);
			run_interactive(argv[0]);
			is_pipline = 0;
		}

		if (is_pipline)
		{
			run_non_interactive(argv);
			break;
		}
	}

	return (0);
}
