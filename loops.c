#include "main.h"

/**
 * hsh - shell loop
 * @info: returns info struct
 * @av: arguement vector from main
 *
 * Return: 0 on success, 1 on error
 */
int hsh(info_t *info, char **av)
{
	ssize_t m =  0;
	int builtin_ret = 0;

	while (m != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		m =  get_input(info);
		if (m != -1)
		{
			set_info(info, av);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: parameter and returns info struct
 *
 * Return:  -1 if builtin not found, 0 if executed successfully,
 *		1 if unsuccessful, -2 if signals exit()
 */
int find_builtin(info_t *info)
{
	int i = -1;
	int built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - finds a command path
 * @info: returns info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], "\t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->arg[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
	{
		info->status = 127;
		print_error(info, "path not found\n");
		}
	}
}

/**
 * fork_cmd - forks exec thread to run cmd
 * @info: parameter and returns struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error :");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
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
				print_error(info, "PERMISSION DENIED\n");
		}
	}
}
