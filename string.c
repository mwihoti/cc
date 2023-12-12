#include "main.h"

/**
 * _strlen - returns length of a string
 * @s: string length to check
 *
 * Return: integer length of a string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
/**
 * _strcmp - performs lexicogarphic comparison of strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: negative if s1 < s2, + if s1 > s2,
 *		0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
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
 * starts_with - checks if it starts with a haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concates strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to buffer dest
 */
char *_strcat(char *dest, char *src)
{
	char *conc = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src++;
	return (conc);
}
