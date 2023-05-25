#include "shell.h"

/**
 * get_sigint - handle The Crtl + c Call in Prompt
 * @sig: Signal Handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
