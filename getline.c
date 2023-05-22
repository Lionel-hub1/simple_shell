#include "shell.h"

/**
 * _getline - Reads a line from a stream and stores it in a buffer.
 * @lineptr: Pointer to the buffer that will store the line.
 * @n: Pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * Return: The number of characters read (including the newline character),
 *         -1 on failure or end-of-file condition.
 */
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

/**
 * _execve - Executes a command by forking a new process.
 * @argv: The argument vector containing the command and its arguments.
 *
 * Return: void.
 */
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

/**
 * _clear - Clears the screen.
 *
 * Return: void.
 */
void _clear(void)
{
	printf("\033c");
}
