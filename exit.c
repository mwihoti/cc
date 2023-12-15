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
	int m, k;
	char *string = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		k = m;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (string);
}
/**
 * *_strconcate - concates two strings
 * @dest: first string
 * @src: second string
 * @n: amount of maximum bytes to be maximally used
 *
 * Return: concated string
 */
char *_strconcate(char *dest, char *src, int n)
{
	int m;
	int k;
	char *string = dest;

	m = 0;
	k = 0;
	while (dest[m] != '\0')
		m++;
	while (src[k] != '\0' && k < n)
	{
		dest[m] = src[k];
		m++;
		k++;
	}
	if (k < n)
		dest[m] = '\0';
	return (string);
}

/**
 * *_strchar - locates a character in a string
 * @s: string to be parsed
 * @c: character to look for
 *
 * Return: (s) pointer to memory area
 */
char *_strchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
