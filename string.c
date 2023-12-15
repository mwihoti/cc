#include "main.h"

/**
 * _strslength - returns length of a string
 * @s: string length to check
 *
 * Return: integer length of a string
 */
int _strslength(char *s)
{
	int n = 0;

	if (!s)
		return (0);

	while (*s++)
		n++;
	return (n);
}
/**
 * _strcompare - performs lexicogarphic comparison of strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: negative if s1 < s2, + if s1 > s2,
 *		0 if s1 == s2
 */
int _strcompare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * start_hay - checks if it starts with a haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_hay(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strsconcate - concates strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to buffer dest
 */
char *_strsconcate(char *dest, char *src)
{
	char *concate = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src++;
	return (concate);
}
