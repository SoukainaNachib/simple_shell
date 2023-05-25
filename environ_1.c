#include "shell.h"

/**
 * cmp_env_name - Compares Env Var Names
 * with The Name Passed.
 * @nenv: Name of the Environment Var
 * @name: Name Passed
 *
 * Return: 0 If Are Not Equal. Another Value if They Are
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int k;

	for (k = 0; nenv[k] != '='; k++)
	{
		if (nenv[k] != name[k])
		{
			return (0);
		}
	}

	return (k + 1);
}

/**
 * _getenv - Get an Environment Var
 * @name: Name Of The Environment Var
 * @_environ: Environment var
 *
 * Return: Value of the Environment Var If is Found.
 * In Other Case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int k, mov;

	/* Initialize Ptr_env Value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all Environment var */
	/* Environ is Declared in the header file */
	for (k = 0; _environ[k]; k++)
	{
		/* If Name And Env Are Equal */
		mov = cmp_env_name(_environ[k], name);
		if (mov)
		{
			ptr_env = _environ[k];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - Prints The Evironment Var
 *
 * @datash: Data Relevant.
 * Return: 1 On Success.
 */
int _env(data_shell *datash)
{
	int k, m;

	for (k = 0; datash->_environ[k]; k++)
	{

		for (m = 0; datash->_environ[k][m]; m++)
			;

		write(STDOUT_FILENO, datash->_environ[k], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
