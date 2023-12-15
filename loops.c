#include "main.h"

/**
 * shell - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell(info_t *info, char **av)
{
	ssize_t n = 0;
	int builtin_shell = 0;

	while (n != -1 && builtin_shell != -2)
	{
		init_info(info);
		if (if_interactive(info))
			_puts("$ ");
		_putscharacter(BUF_FLUSH);
		n = get_lineinput(info);
		if (n != -1)
		{
			sets_info(info, av);
			builtin_shell = finds_command(info);
			if (builtin_shell == -1)
				fork_thread(info);
		}
		else if (if_interactive(info))
			_putchar('\n');
		frees_info(info, 0);
	}
	writes_filehistory(info);
	frees_info(info, 1);
	if (!if_interactive(info) && info->status)
		exit(info->status);
	if (builtin_shell == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_shell);
}

/**
 * finds_command - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int finds_command(info_t *info)
{
	int i, built_cmd = -1;
	builtin_table builtintbl[] = {
		{"exit", _getexit},
		{"env", _currenv},
		{"help", _cdc},
		{"history", _dishistory},
		{"setenv", _currsetenv},
		{"unsetenv", _currunsetenv},
		{"cd", _changedcd},
		{"alias", build_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_cmd = builtintbl[i].func(info);
			break;
		}
	return (built_cmd);
}

/**
 * finds_path - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void finds_path(info_t *info)
{
	char *path = NULL;
	int e, q;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (e = 0, q = 0; info->arg[e]; e++)
		if (!check_delim(info->arg[e], " \t\n"))
			q++;
	if (!q)
		return;

	path = find_path(info, _getenviron(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_thread(info);
	}
	else
	{
		if ((if_interactive(info) || _getenviron(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_thread(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prints_error(info, "not found\n");
		}
	}
}

/**
 * fork_thread - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_thread(info_t *info)
{
	pid_t child_id;

	child_id = fork();
	if (child_id == -1)
	{
		perror("Error:");
		return;
	}
	if (child_id == 0)
	{
		if (execve(info->path, info->argv, gets_environ(info)) == -1)
		{
			frees_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prints_error(info, "Permission denied\n");
		}
	}
}
