#include "shell.h"

/**
 * exit_shell - Handles the exit command of the shell.
 * @infoma: Pointer to the 'infto_t' struct.
 *
 * Return:
 *   -2: Indicates the shell should exit.
 *    1: Indicates an error occurred while converting the argument to an int
 */
int exit_shell(infto_t *infoma)
{
	int exitcheck;

	if (infoma->argv[1])
	{
		/* Convert argument to an integer */
		exitcheck = str_to_int(infoma->argv[1]);
		if (exitcheck == -1)
		{
			infoma->status = 2;
			error_printer(infoma, "Illegal number: "); /*Print error message*/
			print_string(infoma->argv[1]);
			custom_error_putchar('\n');
			return (1);
		}
		/* Set nerror value */
		infoma->nerror = str_to_int(infoma->argv[1]);
		return (-2); /* Return -2 to indicate shell should exit */
	}
	infoma->nerror = -1; /* Set nerror value to -1 */
	return (-2);		 /* Return -2 to indicate shell should exit */
}
