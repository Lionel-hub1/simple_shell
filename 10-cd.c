#include "shell.h"

/**
 * _help - is a process of changing working directory;
 * @infoma:is informant structure of infto_t struct parameter;
 *
 * Return: value 0 for success.
 */
int _help(infto_t *infoma)
{
	char **arv;

	arv = infoma->argv;
	_puts("help call works. Function not yet implemented \n");

	if (0)
		_puts(*arv);

	return (0);
}

/**
 * _cd - is a function to change working or current directory;
 * @infoma: is informant structure of infto_t struct parameter;
 *
 * Return: value 0 for all.
 */
int _cd(infto_t *infoma)
{
	int rval;
	char *dir, *str, buffer[1024];

	str = getcwd(buffer, 1024);
	if (str == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infoma->argv[1])
	{
		dir = environ_getter(infoma, "HOME=");
		if (dir == NULL)
			rval = chdir((dir = environ_getter(infoma, "PWD=")) ? dir : "/");
		else
			rval = chdir(dir);
	}
	else if (custom_strcmp(infoma->argv[1], "-") == 0)
	{
		if (!environ_getter(infoma, "OLDPWD="))
		{
			_puts(str);
			custom_putchar('\n');
			return (1);
		}
		_puts(environ_getter(infoma, "OLDPWD=")), custom_putchar('\n');
		rval = chdir((dir = environ_getter(infoma, "OLDPWD=")) ? dir : "/");
	}
	else
		rval = chdir(infoma->argv[1]);
	if (rval == -1)
	{
		error_printer(infoma, "can't cd to ");
		print_string(infoma->argv[1]), custom_error_putchar('\n');
	}
	else
	{
		custom_setenv(infoma, "OLDPWD", environ_getter(infoma, "PWD="));
		custom_setenv(infoma, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
