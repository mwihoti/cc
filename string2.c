#include "main.h"

/**
 * _strcopy - copies string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcopy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

/**
 * _strduplicate - duplicates string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strduplicate(const char *str)
{
	int s = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	while (*str++)
		s++;
	duplicate = malloc(sizeof(char) * (s + 1));
	if (!duplicate)
		return (NULL);
	for (s++; s--;)
		duplicate[s] = *--str;
	return (duplicate);
}

/**
 * _printstr - prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */

void _printstr(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_writechar(str[m]);
		m++;
	}
}

/**
 * _writechar - writes character to be outputed
 *
 * @c: character to print
 *
 * Return: on success i, -1 on error
 */
int _writechar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
