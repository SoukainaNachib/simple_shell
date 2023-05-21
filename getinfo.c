#include "shell.h"

/**
 * clear_info - Initializes Info_t Struct
 * m: Struct Address
 * Return: Void
 */
void clear_info(info_t *m)
{
	m->arg = NULL;
	m->argv = NULL;
	m->path = NULL;
	m->argc = 0;
}

/**
 * set_info - Initializes Info_t Struct
 * @m: Struct Address
 * @a: Argument vector
 * Return: Void
 */
void set_info(info_t *m, char **a)
{
	int k = 0;

	m->fname = a[0];
	if (m->arg)
	{
		m->argv = strtow(m->arg, " \t");
		if (!m->argv)
		{

			m->argv = malloc(sizeof(char *) * 2);
			if (m->argv)
			{
				m->argv[0] = _strdup(m->arg);
				m->argv[1] = NULL;
			}
		}
		for (k = 0; m->argv && m->argv[k]; k++)
			;
		m->argc = k;

		replace_alias(m);
		replace_vars(m);
	}
}

/**
 * free_info - Frees info_t Struct fields
 * @m: Struct Address
 * @a: True if Freeing all fields
 * Return: Void
 */
void free_info(info_t *m, int a)
{
	ffree(m->argv);
	m->argv = NULL;
	m->path = NULL;
	if (a)
	{
		if (!m->cmd_buf)
			free(m->arg);
		if (m->env)
			free_list(&(m->env));
		if (m->history)
			free_list(&(m->history));
		if (m->alias)
			free_list(&(m->alias));
		ffree(m->environ);
			m->environ = NULL;
		bfree((void **)m->cmd_buf);
		if (m->readfd > 2)
			close(m->readfd);
		_putchar(BUF_FLUSH);
	}
}
