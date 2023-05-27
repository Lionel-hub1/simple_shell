#include "shell.h"

/**
 * mk_alias - is a function to make an alias;
 * @infoma: is informant of infto_t structure's information;
 * @str: is a string of an alias to be set or made;
 *
 * Return: value 0 for success otherwise return 1;
 */
int mk_alias(infto_t *infoma, char *str)
{
	char *ptr;

	ptr = custom_strchr(str, '=');
	if (!ptr)
		return (1);

	if (!*++ptr)
		return (unmk_alias(infoma, str));

	unmk_alias(infoma, str);

	return (end_addnode(&(infoma->alias), str, 0) == NULL);
}

/**
 * unmk_alias - is a function to unmake or to delete an alias;
 * @infoma: is informant of infto_t structure's information;
 * @str: is a string of an alias to unset or to be deleted;
 *
 * Return: value 0 for success otherwise return 1.
 */
int unmk_alias(infto_t *infoma, char *str)
{
	char *ptr;
	char c;
	int rval;/* return value */

	ptr = custom_strchr(str, '=');
	if (!ptr)
		return (1);

	c = *ptr;
	*ptr = 0;
	/* return value on deletion of a node */
	rval = del_nodeidx(&(infoma->alias),
							   index_node(infoma->alias, start_node(infoma->alias, str, -1)));
	*ptr = c;
	return (rval);
}

/**
 * alias_replacer - is a function to replace an alias;
 * @infoma: is informant of infto_t structure's information;
 *
 * Return: value 1 for success otherwise 0 for failure.
 */
int alias_replacer(infto_t *infoma)
{
	strl_t *node;
	int i;
	char *pt;

	for (i = 0; i < 10; i++)
	{
		node = start_node(infoma->alias, infoma->argv[0], '=');
		if (!node)
			return (0); /* return 0 if node is NULL */

		free(infoma->argv[0]);
		pt = custom_strchr(node->str, '=');
		if (!pt)
			return (0); /* return 0 if pt is NULL */

		pt = custom_strdup(pt + 1);
		if (!pt)
			return (0); /* return 0 if pt is NULL */

		infoma->argv[0] = pt;
		free(pt); /* end by freeing pt */
	}

	return (1);
}

/**
 * alias_printer - is a function to print an alias string;
 * @node: is a node related to an alias string;
 *
 * Return: value 0 for success otherwise 1 for failure.
 */
int alias_printer(strl_t *node)
{
	char *sta = NULL, *pt = NULL;

	if (node)
	{
		pt = custom_strchr(node->str, '=');
		sta = node->str;
		while (sta <= pt)
		{
			custom_putchar(*sta);
			sta++;
		}
		custom_putchar('\'');
		_puts(pt + 1);
		_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * _alias - is a mimicing an alias by manual alias details;
 * @infoma: is informant of infto_t structure's information;
 *
 * Return: value 0 for all.
 */
int _alias(infto_t *infoma)
{
	strl_t *node = NULL;
	char *pt = NULL;
	int i = 0;

	if (infoma->argc == 1)
	{
		node = infoma->alias;
		while (node)
		{
			alias_printer(node);/* for printing an alias at current node */
			node = node->next;
		}
		return (0);
	}

	i = 1;
	while (infoma->argv[i])
	{
		pt = custom_strchr(infoma->argv[i], '=');
		if (pt)
		{
			mk_alias(infoma, infoma->argv[i]);/* for setting an alias */
		}
		else
		{
			/* for printing an alias at current index */
			alias_printer(start_node(infoma->alias, infoma->argv[i], '='));
		}
		i++;
	}

	return (0);
}
