#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *newline, *line = *lineptr;
	size_t size = *n;
	int ch;
	size_t i = 0;

	/* To allocate memory for buffer if have not allocated */
	if (line == NULL)
	{
		size = SIZE;
		line = malloc(size);
		if (line == NULL)
			return (-1);
	}

	while ((ch = fgetc(stream)) != EOF)
	{
		if (i + 1 == size)
		{
			/* to double the buffer size for line*/
			size *= 2;
			newline = realloc(line, size);

			if (newline == NULL)
				return (-1);

			line = newline;
			free(newline);
		}

		line[i++] = (char)ch;

		if (ch == '\n')
			break;
	}

	if (i == 0)
	{
		/* this control End Of File(EOF) or error occurred */
		return (-1); /*or by Ctrl + D*/
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
	char **argv;

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
		if (strcmp(line, "clear\n") == 0)
			_clear();
		else
		{
			if (strcmp(line, "\n") != 0)
			{
				argv = cmdtoargv(line);
				_execve(argv);
			}
		}
	}
	free(line);

	return (0);
}

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

void _execve(char **argv)
{
	pid_t pid;
	int rval, len;
	char *cmd;

	if (argv == NULL || argv[0] == NULL)
		return;

	cmd = _which(argv[0]);
	if (cmd == NULL)
	{
		printf("%s: command not found\n", argv[0]);
		return;
	}

	len = strlen(cmd) + 1;
	argv[0] = realloc(argv[0], len);
	snprintf(argv[0], len, "%s", cmd);

	pid = fork();
	if (pid == -1)
		perror("Error");

	if (pid == 0)
	{
		rval = execve(argv[0], argv, NULL);
		if (rval == -1)
			perror("Error");
	}
	else
		wait(NULL);
}

void _clear(void)
{
	printf("\033c");
}
