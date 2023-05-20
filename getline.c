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
	size_t len = 0;
	int line_size;

	while (1)
	{
		printf("$ ");
		line_size = _getline(&line, &len, stdin);
		if (line_size == -1)
		{
			perror("getline");
			exit(1);
		}
		if (strcmp(line, "exit\n") == 0)
			return (0);

		if (strcmp(line, "printenv\n") == 0)
			_printenv();
		else
		{
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
	int i = 0, len;

	if (line == NULL)
		return;

	argv = malloc(SIZE * sizeof(char *));
	if (argv == NULL)
		return;

	str = strdup(line);
	if (str != NULL)
	{
		token = strtok(str, delim);
		cmd = _which(token);
		if (cmd == NULL)
			cmd = token;
		len = strlen(cmd) + 1;
		argv[i] = malloc(len * sizeof(char));
		snprintf(argv[i], len, "%s", cmd);
		i++;
		while (token)
		{
			len = strlen(token) + 1;
			argv[i] = malloc(len * sizeof(char));
			snprintf(argv[i], len, "%s", token);
			i++;
			token = strtok(NULL, delim);
		}
	}

	if (argv[0] == NULL)
	{
		free(str);
		free(argv);
		return;
	}
	execve(argv[0], argv, NULL);
	if (execve(argv[0], argv, NULL) != 0)
	{
		printf("%s: command not found\n", argv[0]);
		free(str);
		free(argv);
		return;
	}
}
