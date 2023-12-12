#include "main.h"

/**
 * *_strncpy - copy a string
 * @dest: destination of string to be copied
 * @src: source string
 * @n: characters to be copied
 *
 * Return: concated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *string = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (string);
}
/**
 * *_strncat - concates two strings
 * @dest: first string
 * @src: second string
 * @n: amount of maximum bytes to be maximally used
 *
 * Return: concated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;
	char *string = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (string);
}

/**
 * *_strchr - locates a character in a string
 * @s: string to be parsed
 * @c: character to look for
 *
 * Return: (s) pointer to memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
