#include "shell.h"

/**
 * start_node - is a function to return node of string strated with prefix;
 * @node: is a pointer to head of linked list;
 * @prefix: is a string to be matched to;
 * @c: is a next character to the next matched prefix with node;
 *
 * Return: matched node otherwise NULL;
 */
strl_t *start_node(strl_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node != NULL)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
		{
			return (node);
		}
		node = node->next;
	}

	return (NULL);
}

/**
 * index_node - is a function to return index of a node;
 * @head: is a pointer to a head of singly linked list;
 * @node: is a pointer to a node of singly linked list;
 *
 * Return: the index of a node in singly linked list otherwise -1.
 */
ssize_t index_node(strl_t *head, strl_t *node)
{
	size_t x = 0;

	while (head != NULL)
	{
		if (head == node)
			return (x);

		head = head->next;
		x++;
	}

	return (-1);
}
