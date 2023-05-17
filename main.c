#include "shell.h"

/**
 * main - Entry Point
 * @c: Argument Count
 * @v: Argument Vector
 *
 * Return: 0 on Success, 1 on Error
 *
 */

int main(int c, char **v)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (c == 2)
	{
		fd = open(v[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(v[0]);
				_eputs(": 0: Can't open ");
				_eputs(v[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, v);
	return (EXIT_SUCCESS);
}
