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
 * _strdup - duplicates string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	int i = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	for (i++; i--;)
		dup[i] = *--str;
	return (dup);
}

/**
 * _puts - prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes character to be outputed
 *
 * @c: character to print
 *
 * Return: on success i, -1 on error
 */
int _putchar(char c)
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
