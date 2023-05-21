#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *new_line, *line = *lineptr;
	size_t size = *n;
	int c;
	size_t i = 0;

	/* Allocate a buffer if one has not already been allocated*/
	if (line == NULL)
	{
		size = INITIAL_SIZE;
		line = malloc(size);
		if (line == NULL)
			return (-1);
	}

	while ((c = fgetc(stream)) != EOF)
	{
		if (i + 1 == size)
		{
			/* Double the buffer size*/
			size *= 2;
			new_line = realloc(line, size);
			if (new_line == NULL)
				return (-1);
			line = new_line;
			free (new_line);
		}
		line[i++] = (char)c;
		if (c == '\n')
			break;
	}

	if (i == 0)
	{
		/* End-of-file or error occurred */
		return (-1);
	}

	line[i] = '\0';
	*lineptr = line;
	*n = size;

	return (i);
}

int main(void)
{
	char *line = NULL;
	size_t len = SIZE;
	int line_size;

	while (1)
	{
		printf("$ ");
		line_size = _getline(&line, &len, stdin);
		if (line_size == -1)
		{
			printf("\n");
			exit(0);
		}

		if (strcmp(line, "exit\n") == 0)
			return (0);

		if (strcmp(line, "printenv\n") == 0)
			_printenv();
		else
		{
			if (strcmp(line, "\n") != 0)
				_execve(line);
		}
	}
	free(line);

	return (0);
}

void _execve(char *line)
{
	char **argv;
	char *cmd, *str, *token, *delim = " \n";
	int i = 0, len, x = 0;

	if (line == NULL)
		return;

	argv = malloc(SIZE * sizeof(char *));
	cmd = malloc(SIZE);
	str = malloc(SIZE);
	token = malloc(SIZE);
	if (argv == NULL || cmd == NULL || str == NULL ||
			token == NULL)
		return;

	str = strdup(line);
	if (str != NULL)
	{
		token = strtok(str, delim);
		while (token)
		{
			len = strlen(token) + 1;
			argv[i] = malloc(len * sizeof(char));
			snprintf(argv[i], len, "%s", token);
			i++;
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
	}

	if (argv[0] == NULL)
	{
		free(str);
		free(argv);
		return;
	}

	if (argv[0] != NULL)
	{
		cmd = _which(argv[0]);
		if (cmd != NULL)
		{
			len = strlen(cmd) + 1;
			argv[0] = realloc(argv[0], len);
			snprintf(argv[0], len, "%s", cmd);
		}
	}
	if (argv != NULL)
	{
		while (argv[x])
		{
			printf("%s\n", argv[x]);
			x++;
		}
		return;
	}

	if (execve(argv[0], argv, NULL) != 0)
	{
		printf("%s: command not found\n", argv[0]);
		free(str);
		while (i <= 0)
		{
			free(argv[i]);
			i--;
		}
		free(argv);
		return;
	}
}
