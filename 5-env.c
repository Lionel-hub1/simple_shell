#include "shell.h"

/**
 * environ_printer - Prints the environment variables.
 * @infoma: Pointer to the `infto_t` struct.
 *
 * Return: 0: Indicates successful execution.
 */
int environ_printer(infto_t *infoma)
{
	/* Print the linked list of environment variables */
	print_linked_list(infoma->env);
	return (0);
}

/**
 * environ_getter - Retrieves the value of an environment variable.
 * @infoma: Pointer to the `infto_t` struct.
 * @name: Name of the environment variable to retrieve.
 *
 * Return:
 *   - Pointer to the value of the environment variable if found.
 *   - NULL if the environment variable is not found.
 */
char *environ_getter(infto_t *infoma, const char *name)
{
	strl_t *list_node = infoma->env;
	char *starter;

	while (list_node)
	{
		/*Check if the node's string starts with the given name*/
		starter = starts_with(list_node->str, name);
		/*If starter is not null and the next character is not null as well*/
		if (starter && *starter)
			return (starter);		 /* Return the pointer */
		list_node = list_node->next; /* Move to the next node */
	}
	return (NULL);
}

/**
 * populate_envlist - Populates the environment variable linked list.
 * @infoma: Pointer to the `infto_t` struct.
 *
 * Return: Always returns 0 to indicate successful execution
 */
int populate_envlist(infto_t *infoma)
{
	strl_t *list_node = NULL;
	size_t index;

	/*Add each environment variable to the linked list*/
	for (index = 0; environ[index]; index++)
		end_addnode(&list_node, environ[index], 0);
	infoma->env = list_node; /* Set the environment variable linked list */
	return (0);
}
