#include "shell.h"

/**
 * main - This function is the entry point for a simple shell
 * @ac: Is the number of arguments
 * @av: Is the argument vector (array of strings)
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main(int ac, char **av)
{
	infto_t infoma[] = {INIT_INFORMA};
	int file_descriptor = 2;

	/* This is a hack to get the file descriptor for stderr */
	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(file_descriptor)
		: "r"(file_descriptor));

	/* Set up the infoma struct */
	if (ac == 2)
	{
		file_descriptor = open(av[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_string(av[0]);
				print_string(": 0: Can't open ");
				print_string(av[1]);
				custom_error_putchar('\n');
				custom_error_putchar(BFLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infoma->readfd = file_descriptor;
	}
	populate_envlist(infoma);
	rd_history(infoma);
	hsh(infoma, av);
	return (EXIT_SUCCESS);
}
