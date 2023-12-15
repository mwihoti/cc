#include "main.h"

/**
 * get_filehistory - get file  history
 * @info: paramet struct
 *
 * Return: allocated string with file
 */
char *get_filehistory(info_t *info)
{
	char *gets, *directory;

	directory = _getenviron(info, "home=");
	if (!directory)
		return (NULL);
	gets = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!gets)
		return (NULL);
	gets[0] = 0;
	_strcpy(gets, directory);
	_strcat(gets, "/");
	_strcat(gets, HIST_FILE);
	return (gets);
}

/**
 * writes_historyfile - creates a file if it exist appeds file
 * @info: parameter struct
 *
 * Return: 1 on succes, else -1
 */

int writes_historyfile(info_t *info)
{
	ssize_t fd;
	char *filename = get_filehistory(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_prstr(node->str, fd);
		_wrfd('\n', fd);
	}
	_wrfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * reads_filehistory - read files history
 * @info: parameter struct
 *
 * Return: histcount on success, otherwise 0
 */
int reads_filehistory(info_t *info)
{
	int j, point = 0,  line_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_filehistory(info);

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
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			builds_history(info, buf + point, line_count++);
			point = j + 1;
		}
	if (point != j)
		builds_history(info, buf + point, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= INT_MAX)
		delete_node_at_index(&(info->history), 0);
	renumbers_list(info);
	return (info->histcount);
}
/**
 * builds_history - addds entry to history linked list
 * @info: structure containing potential arguements
 * @buf: buffer
 * @line_count: history  linecount
 *
 * Return: 0
 */
int builds_history(info_t *info, char *buf, int line_count)
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
 * renumber_list - renumbers history linked list
 * @info: structure containing potential arguements
 *
 * Return: new histcount
 */
int renumber_list(info_t *info)
{
	list_t *node = info->history;
	int m = 0;

	while (node)
	{
		node->num = m++;
		node = node->next;
	}
	return (info->histcount = m);
}
