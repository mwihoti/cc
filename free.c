#include "main.h"

/**
 * _putstr - prints string input
 * @str: string to print
 *
 * Return: nothing
 */

void _putstr(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putscharacter(str[m]);
		m++;
	}
}

/**
 * _putscharacter - writes character to stderr
 * @c: character to print
 *
 * Return: on success 1, -1 on error
 */
int _putcharacter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _wrfd - writes character to fd
 * @c: character to print
 * @fd: file descriptor
 *
 * Return: 1 on success, -1 on error
 */
int _wrfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _prstr - prints an input string
 * @str: string to print
 * @fd: file descriptor
 *
 * Return: number of char put
 */
int _prstr(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _wrfd(*str++, fd);
	}
	return (i);
}
