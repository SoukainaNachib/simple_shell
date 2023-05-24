#include "shell.h"

/**
 * run_from_file - Run shell in non-interactive mode
 * @argv: Array of arguments
 *
 * Return: 0 or 1
 */
int run_from_file(char *argv[])
{
	char *bytes = NULL, *expression = NULL, *command = NULL;
	char **expressions = NULL, **args = NULL;
	int fd, read_bytes, code, i = 0;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[0]);
		exit(1);
	}

	read_bytes = get_input(&bytes, fd);
	if (read_bytes == -1)
	{
		perror(argv[0]);
		exit(1);
	}

	parse_args(&expressions, bytes, read_bytes, NEWLINE);

	while (expressions[i])
	{
		code = parse_and_execute(argv[0], args, expressions[i++]);
		free_main(args, expression, command);
	}

	free_main(expressions, bytes, NULL);
	close(fd);
	exit(code);
}

/**
 * run_non_interactive - Run shell in non-interactive mode
 * @argv: Array of arguments
 *
 * Return: 0 or 1
 */
int run_non_interactive(char *argv[])
{
	char *bytes = NULL, *expression = NULL, *command = NULL;
	char **expressions = NULL, **args = NULL;
	int read_bytes, code, i = 0;

	read_bytes = get_input(&bytes, STDIN_FILENO);
	if (read_bytes == -1)
	{
		perror(argv[0]);
		exit(1);
	}

	parse_args(&expressions, bytes, read_bytes, NEWLINE);

	while (expressions[i])
	{
		code = parse_and_execute(argv[0], args, expressions[i++]);
		free_main(args, expression, command);
	}

	free_main(expressions, NULL, NULL);
	exit(code);
}

/**
 * run_interactive - Run shell in interactive mode
 * @p_name: Program name
 *
 * Return: 0 or 1
 */
int run_interactive(char *p_name)
{
	shell_op operators[] = {
	    {";", 1},
	    {"&&", 2},
	    {"||", 2},
	    {"#", 1}};

	char *line = NULL, *command = NULL, *expression = NULL;
	char **args = NULL;
	shell_op *s_op = NULL;
	ssize_t line_size;
	int code;

	line_size = get_input(&line, STDIN_FILENO);

	if (handle_eof_empty(line, line_size))
		return (1);

	while (line)
	{
		expression = get_line(&line, &s_op, operators);
		if (*expression)
			code = parse_and_execute(p_name, args, expression);

		free_main(args, expression, command);
		if (handle_operator(code, s_op, operators))
			break;
	}

	line = NULL;
	return (code);
}
