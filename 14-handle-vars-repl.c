#include "shell.h"

/**
 * var_replacer - is a function for variable replacing;
 * @infoma: is informant for into_t structure;
 *
 * Return: value 1 if yes otherwise 0 for if not replaced.
 */
int var_replacer(infto_t *infoma)
{
	strl_t *node;
	int i = 0;

	for (i = 0; infoma->argv[i]; i++)
	{
		if (infoma->argv[i][0] != '$' || !infoma->argv[i][1])
			continue; /* if yes continue */

		if (!custom_strcmp(infoma->argv[i], "$?"))
		{
			string_replacer(&(infoma->argv[i]),
							custom_strdup(custom_itoa(infoma->status, 10, 0)));
			continue; /* if yes continue */
		}

		if (!custom_strcmp(infoma->argv[i], "$$"))
		{
			string_replacer(&(infoma->argv[i]),
							custom_strdup(custom_itoa(getpid(), 10, 0)));
			continue; /* if yes continue */
		}

		node = start_node(infoma->env, &infoma->argv[i][1], '=');
		if (node)
		{
			string_replacer(&(infoma->argv[i]),
							custom_strdup(custom_strchr(node->str, '=') + 1));
			continue; /* if yes continue */
		}
		string_replacer(&infoma->argv[i], custom_strdup(""));
	}

	return (0);
}

/**
 * set_infoma - is a function for initialization of infto_t structure;
 * @infoma:  is informant for into_t structure;
 * @av: is arguments vector by informant strucure;
 */
void set_infoma(infto_t *infoma, char **av)
{
	int x = 0;

	infoma->filename = av[0];
	if (infoma->arg)
	{
		infoma->argv = str_to_words(infoma->arg, " \t");
		if (!infoma->argv)
		{
			infoma->argv = malloc(sizeof(char *) * 2);
			if (infoma->argv)
			{
				infoma->argv[0] = custom_strdup(infoma->arg);
				infoma->argv[1] = NULL;
			}
		}

		while (infoma->argv && infoma->argv[x])
			x++;

		infoma->argc = x;

		alias_replacer(infoma);
		var_replacer(infoma);
	}
}

/**
 * free_infoma - is a function to free all infto_t struct fields;
 * @infoma: is informant for into_t structure;
 * @yes: if yes free all files;
 *
 * Return: type is void means nothing to be returned.
 */
void free_infoma(infto_t *infoma, int yes)
{
	str_o_s_free(infoma->argv);
	infoma->argv = NULL;
	infoma->path = NULL;

	if (yes)
	{
		/* cmd buffer */
		if (!infoma->bf_cmd)
			free(infoma->arg);

		/* environment */
		if (infoma->env)
			free_lnlist(&(infoma->env));

		/* history */
		if (infoma->history)
			free_lnlist(&(infoma->history));

		/* alias */
		if (infoma->alias)
			free_lnlist(&(infoma->alias));

		str_o_s_free(infoma->environ);
		infoma->environ = NULL;
		free_buffer((void **)infoma->bf_cmd);

		if (infoma->readfd > 2)
			close(infoma->readfd);

		custom_putchar(BFLUSH);
	}
}

/**
 * clear_infoma - is a function to initialize infto_t struct with NULL;
 * @infoma: is informant for into_t structure;
 *
 * Return: nothing;
 */
void clear_infoma(infto_t *infoma)
{
	infoma->arg = NULL;

	infoma->argv = NULL;

	infoma->path = NULL;

	infoma->argc = 0;
}
