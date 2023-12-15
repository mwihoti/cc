#include "main.h"
/**
 * adds_node - add node to the  start of list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *adds_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memorybyte((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strduplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * adds_node_to_end - adds a node to the end of the list
 * @head: address of pointer head
 * @str: field of node
 * @num: index used of node
 *
 * Return: size of list
 */
list_t *adds_node_to_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memorybyte((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strduplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * prints_list - prints str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t prints_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_printstr(h->str ? h->str : "(nil)");
		_printstr("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * deletes_node_index - deletes node
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deletes_node_index(list_t **head, unsigned int index)
{
	list_t *curr_node, *previous_node;
	unsigned int n = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		curr_node = *head;
		*head = (*head)->next;
		free(curr_node->str);
		free(curr_node);
		return (1);
	}
	curr_node = *head;
	while (curr_node)
	{
		if (n == index)
		{
			previous_node->next = curr_node->next;
			free(curr_node->str);
			free(curr_node);
			return (1);
		}
		n++;
		previous_node = curr_node;
		curr_node = previous_node->next;
	}
	return (0);
}
/**
 * frees_list - frees all node of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void frees_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

