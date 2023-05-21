#include "shell.h"

/**
 * is_cmd - Determines If a File is An Executable Command
 * @inf: The Info Struct
 * @path: Path To The File
 *
 * Return: 1 if True, 0 Otherwise
 */
int is_cmd(info_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates Char
 * @pathstr: The PATH Str
 * @sta: Start Index
 * @sto: Stop Index
 *
 * Return: Pointer to New Buffer
 */
char *dup_chars(char *pathstr, int sta, int sto)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = sta; i < sto; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds This Cmd In The PATH Str
 * @inf: The Info struct
 * @pathstr: The PATH str
 * @cmd: The Cmd to Find
 *
 * Return: Full path of cmd if Found or NULL
 */
char *find_path(info_t *inf, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
