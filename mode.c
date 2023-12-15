#include "main.h"

/**
 *if_ interactive - returns true if in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode otherwise 0
 */
int if_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * check_delim - checks if its a delimeter
 * @c: char to check
 * @delim: delimeter string
 *
 * Return: 1 if true, 0 if false
 */
int check_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _alpha - look for alphabetic character
 * @c: character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _stratoi - converts string to integer
 * @s: string to be converted
 *
 * Return: 0 if no numbers in string otherwise converted number
 */

int _stratoi(char *s)
{
	int n, out_put;
	int signs = 1, flags = 0;
	unsigned int results = 0;

	for (n = 0; s[n] != '\0' && flags != 2; n++)
	{
		if (s[n] == '-')
			signs *= -1;
		if (s[n] >= '0' && s[n] <= '9')
		{
			flags = 1;
			results *= 10;
			results += (s[n] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}
	if (signs == -1)
		out_put = -results;
	else
		out_put = results;
	return (out_put);
}

