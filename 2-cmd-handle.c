#include "shell.h"

/**
 * custorm_fork - This function forks a child process and executes a command.
 * @infoma: Pointer to the infoma structure containing command information.
 */
void custorm_fork(infto_t *infoma)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* Print error message if fork fails */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infoma->path, infoma->argv, find_environ(infoma)) == -1)
		{
			free_infoma(infoma, 1);
			/* Exit with code 126 if execution permission denied */
			if (errno == EACCES)
				exit(126);
			exit(1); /* Exit with code 1 if execve fails */
		}
	}
	else
	{
		/* Wait for the child process to terminate */
		wait(&(infoma->status));
		if (WIFEXITED(infoma->status))
		{
			/* Get the exit status of the child process */
			infoma->status = WEXITSTATUS(infoma->status);
			/* Print error message if permission denied */
			if (infoma->status == 126)
				error_printer(infoma, "Permission denied\n");
		}
	}
}

/**
 * is_executable - Checks if a file at the given path is executable.
 * @infoma: Pointer to the infoma structure (unused in the function).
 * @path: Path of the file to be checked.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int is_executable(infto_t *infoma, char *path)
{
	struct stat st;

	(void)infoma; /* Unused parameter */

	if (!path || stat(path, &st)) /* Check if path is null or stat fails */
		return (0);

	if (st.st_mode & S_IFREG) /* Check if the file is a regular file */
	{
		return (1); /* File is executable */
	}

	return (0); /* File is not executable */
}

/**
 * duplicate_char - Creates a duplicate string from a portion of input string
 * @path_txt: Is the input string.
 * @start: Is the starting index of the portion to duplicate
 * @stop: Is the ending index of the portion to duplicate
 *
 * Return: A pointer to the duplicated string
 */
char *duplicate_char(char *path_txt, int start, int stop)
{
	static char buffer[1024];
	int index1 = 0, index2 = 0;

	for (index2 = 0, index1 = start; index1 < stop; index1++)
		if (path_txt[index1] != ':')
			buffer[index2++] = path_txt[index1];
	buffer[index2] = 0;
	return (buffer);
}

/**
 * cmnd_finder - Finds and executes a command based on the input information.
 * @infoma: Pointer to the `infto_t` structure containing command information.
 */
void cmnd_finder(infto_t *infoma)
{
	char *cmd_path = NULL;
	int index, num_args;

	infoma->path = infoma->argv[0];
	/* Increment line count if countline_flag is set */
	if (infoma->countline_flag == 1)
	{
		infoma->count_line++;
		infoma->countline_flag = 0;
	}
	/* Count the number of non-delimiter arguments */
	for (index = 0, num_args = 0; infoma->arg[index]; index++)
		if (!is_delimeter(infoma->arg[index], " \t\n"))
			num_args++;
	/* If no arguments, return */
	if (num_args == 0)
		return;
	/* Find the executable path */
	cmd_path = path_finder(infoma, environ_getter(infoma, "PATH="),
						   infoma->argv[0]);
	if (cmd_path)
	{
		/* If path is found, update the command path and execute */
		infoma->path = cmd_path;
		custorm_fork(infoma);
	}
	else
	{
		/* If path is not found, check if the command is executable */
		if ((is_interactive(infoma) || environ_getter(infoma, "PATH=") ||
			 infoma->argv[0][0] == '/') &&
			is_executable(infoma, infoma->argv[0]))
			custorm_fork(infoma);
		else if (*(infoma->arg) != '\n') /* Print error if command not found */
		{
			infoma->status = 127;
			error_printer(infoma, "not found\n");
		}
	}
}
