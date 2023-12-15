#include "main.h"

/**
 * exec_cmd - determine if a file is executable command
 * @info: info struct
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int exec_cmd(info_t *info, char *path)
{
	struct stat str;

	(void)info;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * duplicate_char - duplicates characters
 * @pathstr: path string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_char(char *pathstr, int start, int stop)
{
	static char bufs[1024];
	int n = 0;
	int i = 0;

	for (i = 0, n = start; n < stop; n++)
		if (pathstr[n] != ':')
			bufs[i++] = pathstr[n];
	bufs[i] = 0;
	return (bufs);
}

/**
 * cmd_path - finds cmd in path string
 * @info: info struct
 * @pathstr: path string
 * @cmd: cmd to find
 *
 * Return: full path of cmd or NULL
 */

char *cmd_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0;
	int current_pos = 0;
	char *fpath;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (exec_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			fpath = duplicate_char(pathstr, current_pos, i);
			if (!*fpath)
				_strcat(fpath, cmd);
			else
			{
				_strcat(fpath, "/");
				_strcat(fpath, cmd);
			}
			if (exec_cmd(info, fpath))
				return (fpath);
			if (!pathstr[i])
				break;
			if (!pathstr[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}

