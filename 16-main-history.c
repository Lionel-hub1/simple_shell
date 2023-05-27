#include "shell.h"

/**
 * uhistory - a function to displays list of histry by one cmd per line;
 * @infoma: is informa or a constant structure for arguments;
 *
 *  Return: value 0 for success;
 */
int uhistory(infto_t *infoma)
{
	print_ls(infoma->history);

	return (0);
}

/**
 * lnls_len - is  a function for finding the length of linked list;
 * @h: is a pointer to head of linked list;
 *
 * Return: the length of singly linked list;
 */
size_t lnls_len(const strl_t *h)
{
	size_t x = 0;

	while (h != NULL)
	{
		h = h->next;
		x++;
	}

	return (x);
}

/**
 * str_list - is a function to return an array of strings;
 * @head: is a pointer to a head of singly linked list;
 *
 * Return: an array of string of singly linked list.
 */
char **str_list(strl_t *head)
{
	strl_t *node = head;
	size_t x = lnls_len(head), y;
	char **arg;
	char *str;

	if (!head || !x)
		return (NULL);

	arg = malloc(sizeof(char *) * (x + 1)); /* memmory allocation */
	if (!arg)
		return (NULL);

	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(arg[y]); /* free every argv's index */

			free(arg);
			return (NULL);
		}

		str = custom_strcpy(str, node->str);
		arg[x] = str;
	}
	arg[x] = NULL;
	return (arg);
}
