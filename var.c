#include "shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: Head OF linked List
 * @in: Input Str
 * @data: data Structure
 * Return: NO Return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, k, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (k = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, k, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[k] == _envr[row][chr])
				k++;
			else
				break;
		}
	}

	for (k = 0; in[k]; k++)
	{
		if (in[k] == ' ' || in[k] == '\t' || in[k] == ';' || in[k] == '\n')
			break;
	}

	add_rvar_node(h, k, NULL, 0);
}

/**
 * check_vars - Check The typed Var if  is $$ or $?
 *
 * @h: Head of The Linked List
 * @in: Input str
 * @st: Last Status of Shell
 * @data: Data Struc
 * Return: NO Return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int k, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (k = 0; in[k]; k++)
	{
		if (in[k] == '$')
		{
			if (in[k + 1] == '?')
				add_rvar_node(h, 2, st, lst), k++;
			else if (in[k + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), k++;
			else if (in[k + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[k + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[k + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[k + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[k + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + k, data);
		}
	}

	return (k);
}

/**
 * replaced_input - Replaces Str Into Var
 *
 * @head: Head Of The Linked List
 * @input: Input Str
 * @new_input: New input sSr (replaced)
 * @nlen: new length
 * Return: replaced str
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int m, j, k;

	indx = *head;
	for (j = m = 0; m < nlen; m++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[m] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				m--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[m] = indx->val[k];
					m++;
				}
				j += (indx->len_var);
				m--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[m] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls Functions to Replace str into vars
 *
 * @input: Input Str
 * @datash: Data Struc
 * Return: Replaced Str
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
