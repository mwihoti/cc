#include "main.h"

/**
 * **splitstr - splits string into words
 * @str: input string
 * @d: delimeter dtring
 *
 * Return: pointer to an array of strings else NULL
 */
char **splitstr(char *str, char *d)
{
	int b, v, k, m, num_words = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (b = 0; str[b] != '\0'; b++)
		if (!check_delim(str[b], d) && (check_delim(str[b + 1], d) || !str[b + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	ss = malloc((1 + num_words) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (b = 0, v = 0; v < num_words; v++)
	{
		while (check_delim(str[b], d))
			b++;
		k = 0;
		while (!check_delim(str[b + k], d) && str[b + k])
			k++;
		ss[v] = malloc((k + 1) * sizeof(char));
		if (!ss[v])
		{
			for (k = 0; k < v; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ss[v][m] = str[b++];
		ss[v][m] = 0;
	}
	ss[v] = NULL;
	return (ss);
}
/**
 * **splitstr2 - splits a string into words
 * @str: input string
 * @d: delimeter
 *
 * Return: pointer to an array of strings
 */

char **splitstr2(char *str, char d)
{
	int i, j, k, m, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0';  i++)
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; m < k; m++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

