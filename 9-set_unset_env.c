#include "shell.h"

/**
 * misetenv - is a function to set environment;
 * @infoma: is informant structure of infto_t struct parameter;
 *  Return: value 0 for all.
 */
int misetenv(infto_t *infoma)
{
	if (infoma->argc != 3)
	{
		/* error message of incorect arguments number */
		print_string("incorrect number of arguments\n");

		return (1);
	}
	if (custom_setenv(infoma, infoma->argv[1], infoma->argv[2]))
		return (0);

	return (1);
}

/**
 * miunsetenv - is a function to delete environmental variable;
 * @infoma: is informant structure of infto_t struct parameter;
 *
 * Return: value 0 for all.
 */
int miunsetenv(infto_t *infoma)
{
	int i;

	if (infoma->argc == 1)
	{
		/* error message of few arguments */
		print_string("too few arguments\n");

		return (1);
	}
	for (i = 1; i <= infoma->argc; i++)
		custom_unsetenv(infoma, infoma->argv[i]);

	return (0);
}

/**
 * find_environ - is a function to find the external environment;
 * @infoma: is informant structure of infto_t struct parameter;
 *
 * Return: value 0 for all;
 */
char **find_environ(infto_t *infoma)
{
	if (!infoma->environ || infoma->changed_env)
	{
		infoma->environ = str_list(infoma->env);
		infoma->changed_env = 0;
	}

	return (infoma->environ);
}

/**
 * custom_unsetenv - This function unset an environment variable.
 * @infoma: Pointer to the shell information struct.
 * @var: The variable to unset.
 *
 * Return: 0 if variable is not found or invalid, otherwise
 * returns the value of `infoma->changed_env`.
 */
int custom_unsetenv(infto_t *infoma, char *var)
{
	strl_t *list_node = infoma->env;
	size_t index = 0;
	char *ptr;

	if (!list_node || !var)
		return (0);

	while (list_node)
	{
		/* Check if the variable starts with the given name */
		ptr = starts_with(list_node->str, var);
		if (ptr && *ptr == '=')
		{
			/* if found Delete the node */
			infoma->changed_env = del_nodeidx(&(infoma->env), index);
			index = 0;				 /* Reset index */
			list_node = infoma->env; /* Reset list_node */
			continue;
		}
		list_node = list_node->next; /* Move to the next node */
		index++;					 /* Increment index */
	}
	return (infoma->changed_env); /* Return 1 if deleted, 0 otherwise */
}

/**
 * custom_setenv - Set an environment variable.
 * @infoma: Pointer to the shell information struct.
 * @var: The variable name.
 * @value: The value to assign to the variable.
 *
 * Return: 0 if successful, otherwise returns 1 if memory
 * allocation fails or 0 if invalid input.
 */
int custom_setenv(infto_t *infoma, char *var, char *value)
{
	char *the_buffer = NULL;
	strl_t *current_node;
	char *ptr;

	if (!var || !value)
		return (0);

	the_buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!the_buffer)
		return (1);
	custom_strcpy(the_buffer, var);
	custom_strcat(the_buffer, "=");
	custom_strcat(the_buffer, value);
	/* Set current_node to the head of the list */
	current_node = infoma->env;
	while (current_node)
	{
		ptr = starts_with(current_node->str, var);
		if (ptr && *ptr == '=')
		{
			/* if found replace the node */
			free(current_node->str);
			current_node->str = the_buffer;
			infoma->changed_env = 1; /* Set changed_env to 1 */
			return (0);
		}
		current_node = current_node->next; /* Move to the next node */
	}
	end_addnode(&(infoma->env), the_buffer, 0); /* Add the new node */
	free(the_buffer);							/* Free the buffer */
	infoma->changed_env = 1;					/* Set changed_env to 1 */
	return (0);
}
