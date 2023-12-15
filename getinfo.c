#include "main.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */

void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * sets_info - initializes info_t struct
 * @info: struct address
 * @av: arguement vector
 */
void sets_info(info_t *info, char **av)
{
	int m = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->arg)
		{
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
		{
			info->argv[0] = _strdup(info->arg);
			info->argv[1] = NULL;
		}
	}
	for (m = 0; info->argv && info->argv[m]; m++)
		;
	info->argc = m;

	replace_alias(info);
	replace_vars(info);
}
}

/**
 * frees_info - frees info_t struct felds
 * @info: struct address
 * @all: free all fields
 */

void frees_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			frees_list(&(info->env));
		if (info->history)
			frees_list(&(info->history));
		if (info->alias)
			frees_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
