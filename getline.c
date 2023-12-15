#include "main.h"

/**
 * inputs_buffer - buffers commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t inputs_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t m = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sign_Handler);
#if USE_GETLINE
		m = getline(buf, &len_p, stdin);
#else
		m = _getnextline(info, buf, &len_p);
#endif
		if (m > 0)
		{
			if ((*buf)[m - 1] == '\n')
			{
				(*buf)[m - 1] = '\0';
				m--;
			}
			info->linecount_flag = 1;
			removes_comments(*buf);
			builds_history(info, *buf, info->histcount++);
			{
				*len = m;
				info->cmd_buf = buf;
			}
		}
	}
	return (m);
}
/**
 * get_lineinput - gets line string
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_lineinput(info_t *info)
{
	static char *buf;
	static size_t j, k, len;
	ssize_t m = 0;
	char **bufs_p = &(info->arg), *point;

	_putchar(BUF_FLUSH);
	m = inputs_buffer(info, &buf, &len);
	if (m == -1)
		return (-1);
	if (len)
	{
		k =  j;
		point = buf + k;

		check_chain(info, buf, &k, j, len);
		while (k < len)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}
		j = k + 1;
		if (j >= len)
		{
			j = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*bufs_p = point;
		return (_strlen(point));
	}
	*bufs_p = buf;
	return (m);
}

/**
 * reads_buffer - reads a buffer
 * @info: parameter struct
 * @buf: bufffer
 * @i: size
 *
 * Return: r
 */
ssize_t reads_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t m = 0;

	if (*i)
		return (0);
	m = read(info->readfd, buf, READ_BUF_SIZE);
	if (m >= 0)
		*i = m;
	return (m);
}

/**
 * _getnextline - gets the next line from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getnextline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t m = 0;
	ssize_t s = 0;
	char *point  = NULL, *new_point = NULL, *c;

	point = *ptr;
	if (point && length)
		s = *length;
	if (i ==  len)
		i = len = 0;

	m = reads_buffer(info, buf, &len);
	if (m == -1 || (m == 0 && len == 0))
		return (-1);

	c = _strchar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_point = _realloc(point, s, s ? s + k : k + 1);
	if (!new_point)
		return (point ? free(point), -1 : -1);
	if (s)
		_strconcate(new_point, buf + i, k - i);
	else
		_stringcpy(new_point, buf + i, k - i + 1);

	s += k - i;
	i = k;
	point = new_point;

	if (length)
		*length = s;
	*ptr = point;
	return (s);
}

/**
 * sign_Handler - blocks ctrl c
 * @sig_num: signal number
 *
 * Return: void
 */
void sign_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
