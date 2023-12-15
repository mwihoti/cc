#include "main.h"

/**
 * _currenv - print current enviroment
 * @info: maintain constant function prototype
 *
 * Return: always 0
 */
int _currenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenviron - gets value of environ variable
 * @info: structuure with arguements
 *
 * @name: env var name
 * Return: value
 */
char *_getenviron(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *point;

	while (node)
	{
		point = starts_with(node->str, name);
		if (point && *point)
			return (point);
		node = node->next;
	}
	return (NULL);
}

/**
 * _currsetenv - initializes enviroment variable
 *
 * @info: contains potential arguements
 *
 * Return: always 0
 */
int _currsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Number of arguement is wrong\n");
		return (1);
	}
	if (_setsenviron(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _currunsetenv - removes enviroment variable
 * @info: structure containing arguements
 *
 * Return: always 0
 */

int _currunsetenv(info_t *info)
{
	int m;

	if (info->argc == -1)
	{
		_eputs("Less number of arguements\n");
		return (1);
	}
	for (m = 1; m <= info->argc; m++)
		_unsetenviron(info, info->argv[m]);

	return (0);
}

/**
 * populates_environ_list - env linked list
 * @info: structure with potential arguements
 *
 * Return: always 0
 */
int populates_environ_list(info_t *info)
{
	list_t *node = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_node_end(&node, environ[m], 0);
	info->env = node;
	return (0);
}
