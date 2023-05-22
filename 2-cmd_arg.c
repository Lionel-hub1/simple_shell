#include "shell.h"

/**
 * cmdtoargv - Converts a command string to an argument vector.
 * @line: The command string to be converted.
 *
 * Return: The argument vector.
 */
char **cmdtoargv(char *line)
{
	char **argv;
	char *str, *token, *delim = " \n";
	int i = 0, len;

	if (line == NULL)
		return (NULL);

	argv = malloc(SIZE * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	str = strdup(line);
	if (str != NULL)
	{
		token = strtok(str, delim);
		while (token)
		{
			len = strlen(token) + 1;
			argv[i] = malloc(len * sizeof(char));
			if (argv[i] == NULL)
			{
				perror("malloc");
				return (NULL);
			}
			snprintf(argv[i], len, "%s", token);
			i++;
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
	}

	return (argv);
}
