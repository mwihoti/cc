#include "main.h"

/**
 * _myenv - print current enviroment
 * @info: maintain constant function prototype
 *
 * Return: always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets value of environ variable
 * @info: structuure with arguements
 *
 * @name: env var name
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initializes enviroment variable
 *
 * @info: contains potential arguements
 *
 * Return: always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Number of arguement is wrong\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - removes enviroment variable
 * @info: structure containing arguements
 *
 * Return: always 0
 */

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == -1)
	{
		_eputs("Less number of arguements\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - env linked list
 * @info: structure with potential arguements
 *
 * Return: always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = mode;
	return (0);
}
