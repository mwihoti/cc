#include "main.h"

/**
 * gets_environ - returns string to copy
 * @info: struct containing potential  arguements
 *
 * Return: always 0
 */
char **gets_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenviron - remove enviroment variable
 * @info: struct containing arguements
 *
 * Return: 1 on delete else 0
 * @var: string env var
 */
int _unsetenviron(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t m = 0;
	char *point;

	if (!node || !var)
		return (0);

	while (node)
	{
		point = starts_with(node->str, var);
		if (point && *point == '=')
		{
			info->env_changed = deletes_node_index(&(info->env), m);
			m = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		m++;
	}
	return (info->env_changed);
}
/**
 * _setsenviron - initializes variable
 *
 * @info: structure containing arguements
 *
 * @var: string env property
 *
 * @value: string env value
 *
 * Return: always 0
 */
int _setsenviron(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *s;

	if (!var || !value)
		return (0);

	buf  = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		s = starts_with(node->str, var);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	adds_node_to_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
