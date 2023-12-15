#include "main.h"
/**
 * _dishistory - displays history list
 *
 * @info: structure containing arguements
 *
 * Return: always 0
 */
int _dishistory(info_t *info)
{
	prints_list(info->history);
	return (0);
}
/**
 * sets_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 *
 * Return: always 0 on success, 1 on error
 */
int sets_alias(info_t *info, char *str)
{
	char *point, m;
	int set;

	point = _strchar(str, '=');
	if (!point)
		return (1);
	m = *point;
	*point = 0;
	set = deletes_node_index(&(info->alias),
			get_index(info->alias, node_to_start(info->alias, str, -1)));
	*point = m;
	return (set);
}

/**
 * string_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 *
 * Return: 0 on success else 1
 */
int string_alias(info_t *info, char *str)
{
	char *point;

	point = _strchar(str, '=');

	if (!point)
	return (1);
	if (!*++point)
		return (sets_alias(info, str));
	sets_alias(info, str);
	return (adds_node_to_end(&(info->alias), str, 0) == NULL);
}

/**
 * prints_alias - prints string alias
 * @node: node alias
 *
 * Return: always 0 on succes, 1 on error
 */
int prints_alias(list_t *node)
{
	char *point = NULL, *n = NULL;

	if (node)
	{
		point = _strchar(node->str, '=');
		for (n  = node->str; n <= point; n++)
			_writechar(*n);
		_writechar('\'');
		_printstr(point + 1);
		_printstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * build_alias - same as built alias
 * @info: structure containing potential arguements
 *
 * Return: 0 always
 */

int build_alias(info_t *info)
{
	int s = 0;
	char *point = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			prints_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (s = 1; info->argv[s]; s++)
	{
		point = _strchar(info->argv[s], '=');
		if (point)
			string_alias(info, info->argv[s]);
		else
			prints_alias(node_to_start(info->alias, info->argv[s], '='));
	}
	return (0);
}
