#include "shell.h"

/**
 * _addnode - is a function to add node at start of singly linked list;
 * @head: is a pointer to the head node;
 * @str: is a string of node's field;
 * @num: is node's index of history linked list;
 *
 * Return: value equal to the size of singly linked list;
 */
strl_t *_addnode(strl_t **head, const char *str, int num)
{
	strl_t *newhead;

	if (!head)
		return (NULL);

	newhead = malloc(sizeof(strl_t));
	if (!newhead)
		return (NULL);

	memory_set((void *)newhead, 0, sizeof(strl_t));
	newhead->num = num;
	if (str)
	{
		newhead->str = custom_strdup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}

	newhead->next = *head;
	*head = newhead;
	return (newhead);
}

/**
 * end_addnode - is a function to add node at the end of linked list;
 * @head: is a pointer to the head node;
 * @str: is a string of node's field;
 * @num: is node's index of history linked list;
 *
 * Return: value equal to the size of singly linked list;
 */
strl_t *end_addnode(strl_t **head, const char *str, int num)
{
	strl_t *newnode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newnode = malloc(sizeof(strl_t));
	if (!newnode)
		return (NULL);

	memory_set((void *)newnode, 0, sizeof(strl_t));
	newnode->num = num;

	if (str)
	{
		newnode->str = custom_strdup(str);
		if (!newnode->str)
		{
			free(newnode);

			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	else
		*head = newnode;

	return (newnode);
}

/**
 * del_nodeidx - is a function to delete node at a certain index;
 * @head: is a pointer to pointing head node;
 * @index: is index where to delete a node;
 *
 * Return: value 1 for true otherwise 0;
 */
int del_nodeidx(strl_t **head, unsigned int index)
{
	unsigned int i = 0;
	strl_t *node, *prevnode;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);

		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prevnode->next = node->next;
			free(node->str);
			free(node);

			return (1);
		}
		i++;
		prevnode = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_lnlist - a function to free all linked listt;
 * @p_hd: is a pointer to pointing head node for storing pointer's address;
 *
 * Return: nothing.
 */
void free_lnlist(strl_t **p_hd)
{
	strl_t *node, *nextnode, *head;

	if (!p_hd || !*p_hd)
		return;

	head = *p_hd;
	node = head;
	while (node)
	{
		nextnode = node->next;
		free(node->str);
		free(node);
		node = nextnode;
	}

	*p_hd = NULL;
}
