#include "shell.h"

/**
 * path_finder - This function finds the executable path for a command.
 * @infoma: Pointer to the `infto_t` structure containing command information
 * @path_txt: Text containing the colon-separated paths to search.
 * @cmd: The command to find.
 *
 * Return: The executable path if found, otherwise NULL.
 */
char *path_finder(infto_t *infoma, char *path_txt, char *cmd)
{
	int i = 0, this_position = 0;
	char *the_path;

	if (!path_txt)
		return (NULL);

	/* Check if the command starts with "./" & is executable in directory */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(infoma, cmd))
			return (cmd);
	}
	while (1)
	{
		/* Split path_txt based on ':' delimiter */
		if (!path_txt[i] || path_txt[i] == ':')
		{
			/* Create path, combining current path segment and the command */
			the_path = duplicate_char(path_txt, this_position, i);
			if (!*the_path)
				custom_strcat(the_path, cmd);
			else
			{
				custom_strcat(the_path, "/");
				custom_strcat(the_path, cmd);
			}
			/* Check if the constructed path is executable */
			if (is_executable(infoma, the_path))
				return (the_path);
			if (!path_txt[i])
				break;
			this_position = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_interactive - Checks if the program is running in interactive mode.
 * @infoma: Pointer to the `infto_t` structure containing command information.
 *
 * Return: 1 if running in interactive mode, 0 otherwise.
 */
int is_interactive(infto_t *infoma)
{
	/* Check if stdin is terminal and the read fd is within the range [0,2] */
	return (isatty(STDIN_FILENO) && infoma->readfd <= 2);
}

/**
 * is_delimeter - This function is for checking if a character is a delimiter.
 * @c: The character to be checked.
 * @delimiter: The string containing delimiters.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimeter(char c, char *delimiter)
{
	/* Iterate through the delimiter string and check it */
	while (*delimiter)
		if (*delimiter++ == c)
			return (1); /* Return 1 on success */
	return (0);
}

/**
 * error_printer - Prints an error message to standard error.
 * @infoma: Pointer to the 'infto_t' struct.
 * @error_str: The error message string to be printed.
 *
 * This function prints an error message with the following format:
 *   <filename>: <line>: <command>: <error message>
 */
void error_printer(infto_t *infoma, char *error_str)
{
	print_string(infoma->filename);
	print_string(": ");
	print_decimals(infoma->count_line, STDERR_FILENO);
	print_string(": ");
	print_string(infoma->argv[0]);
	print_string(": ");
	print_string(error_str);
}
