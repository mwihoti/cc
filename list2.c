#include "main.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to firrst node
 *
 * Return: list size
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns array of string of list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head);
	size_t j;
	char **strings;
	char *string;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strings);
			return (NULL);
		}
		string = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i]  = NULL;
	return (strings);
}

/**
 * print_list - prints all elements of a list_t
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *p)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with -return node string that starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: character after prefix match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = starts_with(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}


