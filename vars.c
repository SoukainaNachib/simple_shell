#include "shell.h"

/**
 * is_chain - Test If Current char In Buffer is a Chain Delim
 * @inf: The Parameter Struct
 * @buf: The Char Buffer
 * @pb: Address Of Current Position In Buf
 *
 * Return: 1 If chain Delimeter, 0 Otherwise
 */
int is_chain(info_t *inf, char *buf, size_t *pb)
{
	size_t k = *pb;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found End of this Command */
	{
		buf[k] = 0; /* replace Semicolon with Null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pb = k;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: The Parameter Struct
 * @buf: The Char Buffer
 * @pb: Address of Current Position in Buf
 * @i: Starting Position In Buf
 * @len: Length Of Buf
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buf, size_t *pb, size_t i, size_t len)
{
	size_t k = *pb;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*pb = k;
}

/**
 * replace_alias - Replaces an Aliases In The Tokenized String
 * @inf: The Parameter Struct
 *
 * Return: 1 If Replaced, 0 Otherwise
 */
int replace_alias(info_t *inf)
{
	int k;
	list_t *node;
	char *p;

	for (k = 0; k < 10; k++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces Vars In The Tokenized Str
 * @inf: The Parameter Struct
 *
 * Return: 1 If Replaced, 0 Otherwise
 */
int replace_vars(info_t *inf)
{
	int k = 0;
	list_t *node;

	for (k = 0; inf->argv[k]; k++)
	{
		if (inf->argv[k][0] != '$' || !inf->argv[k][1])
			continue;

		if (!_strcmp(inf->argv[k], "$?"))
		{
			replace_string(&(inf->argv[k]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[k], "$$"))
		{
			replace_string(&(inf->argv[k]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[k][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[k]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces Str
 * @old: Address Of Old Str
 * @new: new Str
 *
 * Return: 1 if Replaced, 0 Otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
