#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
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

		/* Call _printenv function to print environment variables */
		if (strcmp(line, "printenv\n") == 0 ||
				strcmp(line, "env\n") == 0)
			_printenv();
		/* Call _clear function to clear the terminal screen */
		if (strcmp(line, "clear\n") == 0)
			_clear();
		/* Call _execve function to execute the command with arguments */
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
