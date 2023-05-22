#include "shell.h"

/**
 * get_history_file - Gets the History File
 * @m: Parameter Struct
 * Return: Allocated String Containg History File
 */

char *get_history_file(info_t *m)
{
	char *buffr, *d;

	d = _getenv(m, "HOME=");
	if (!d)
		return (NULL);
	buffr = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!buffr)
		return (NULL);
	buffr[0] = 0;
	_strcpy(buffr, d);
	_strcat(buffr, "/");
	_strcat(buffr, HIST_FILE);
	return (buffr);
}

/**
 * write_history - Creates a File, or Appends to an Existing File
 * @m: the Parameter Struct
 * Return: 1 on success
 */
int write_history(info_t *m)
{
	ssize_t fd;
	char *filn = get_history_file(m);
	list_t *n = NULL;

	if (!filn)
		return (-1);

	fd = open(filn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filn);
	if (fd == -1)
		return (-1);
	for (n = m->history; n; n = n->next)
	{
		_putsfd(n->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads History From file
 * @m: the Parameter Struct
 * Return: histcount on success
 */
int read_history(info_t *m)
{
	int a, lst = 0, linecnt = 0;
	ssize_t fd, rlen, fsz = 0;
	struct stat l;
	char *buffr = NULL, *filn = get_history_file(m);

	if (!filn)
		return (0);

	fd = open(filn, O_RDONLY);
	free(filn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &l))
		fsz = l.st_size;
	if (fsz < 2)
		return (0);
	buffr = malloc(sizeof(char) * (fsz + 1));
	if (!buffr)
		return (0);
	rlen = read(fd, buffr, fsz);
	buffr[fsz] = 0;
	if (rlen <= 0)
		return (free(buffr), 0);
	close(fd);
	for (a = 0; a < fsz; a++)
		if (buffr[a] == '\n')
		{
			buffr[a] = 0;
			build_history_list(m, buffr + lst, linecnt++);
			lst = a + 1;
		}
	if (lst != a)
		build_history_list(m, buffr + lst, linecnt++);
	free(buffr);
	m->histcount = linecnt;
	while (m->histcount-- >= HIST_MAX)
		delete_node_at_index(&(m->history), 0);
	renumber_history(m);
	return (m->histcount);
}

/**
 * build_history_list - Adds Entry to a History Kinked List
 * @m: Structure Containing Potential Arguments
 * @buffr: buffer
 * @linecnt: the History Linecount
 * Return: Always 0
 */
int build_history_list(info_t *m, char *buffr, int linecnt)
{
	list_t *n = NULL;

	if (m->history)
		n = m->history;
	add_node_end(&n, buffr, linecnt);

	if (!m->history)
		m->history = n;
	return (0);
}

/**
 * renumber_history - Renumbers the History Linked List After Changes
 * @m: Structure Containing Potential Arguments
 * Return: the New Histcount
 */
int renumber_history(info_t *m)
{
	list_t *n = m->history;
	int a = 0;

	while (n)
	{
		n->N = a++;
		n = n->next;
	}
	return (m->histcount = a);
}
