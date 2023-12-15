#include "main.h"

/**
 * get_history_file - get file  history
 * @info: paramet struct
 *
 * Return: allocated string with file
 */
char *get_history_file(info_t *info)
{
	char *get, *directory;

	directory = _getenviron(info, "home=");
	if (!directory)
		return (NULL);
	get = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!get)
		return (NULL);
	get[0] = 0;
	_strcpy(get, directory);
	_strcat(get, "/");
	_strcat(get, HIST_FILE);
	return (get);
}

/**
 * write_history - creates a file if it exist appeds file
 * @info: parameter struct
 *
 * Return: 1 on succes, else -1
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read files history
 * @info: parameter struct
 *
 * Return: histcount on success, otherwise 0
 */
int read_history(info_t *info)
{
	int i, last = 0,  line_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= INT_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - addds entry to history linked list
 * @info: structure containing potential arguements
 * @buf: buffer
 * @line_count: history  linecount
 *
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list
 * @info: structure containing potential arguements
 *
 * Return: new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

