#include "shell.h"

/**
 * _getenv - is a function to find environment of a given name;
 * @name: is name to find it's value in environment;
 *
 * Return: value(string) of a given environment name.
 */
char *_getenv(const char *name)
{
	size_t nlen = strlen(name);
	char *env, *str, *delim = "=";

	while (*environ)
	{
		str = strdup(*environ);
		env = strtok(str, delim);
		while (env)
		{
			if (strncmp(name, env, nlen) == 0)
			{
				env = strtok(NULL, delim);
				return (env);
			}
			env = strtok(NULL, delim);
		}
		free(str);
		environ++;
	}

	return (NULL);
}

/**
 * _printenv - is function to print environment;
 *
 * Return: type is void.
 */
void _printenv(void)
{
	char *envcp, *env;
	char **envir = environ;

	while (*envir)
	{
		envcp = strdup(*envir);
		env = strtok(envcp, "\n");
		while (env)
		{
			printf("%s\n", env);
			env = strtok(NULL, "\n");
		}
		free(envcp);
		envir++;
	}
}

/**
 * _setenv - is function to set environment variable;
 * @name: name of variable;
 * @value: value of a variable to be set;
 * @overwrite: if it is non zero have to overwrite existed variable;
 *
 * Return: value 0 for success otherwise -1.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *envar = _getenv(name), *newvar;
	size_t nlen = strlen(name), vlen = strlen(value);
	size_t totlen = nlen + vlen + 2;

	if (envar != NULL)
	{
		if (overwrite == 0)
			return (0);

		newvar = malloc(totlen);
		if (newvar == NULL)
		{
			perror("malloc");
			return (-1);
		}
		snprintf(newvar, totlen, "%s=%s", name, value);
		if (putenv(newvar) != 0)
		{
			perror("putenv");
			return (-1);
		}
	}
	else
	{
		newvar = malloc(totlen);
		if (newvar == NULL)
		{
			perror("malloc");
			return (-1);
		}
		snprintf(newvar, totlen, "%s=%s", name, value);
		if (putenv(newvar) != 0)
		{
			perror("putenv");
			return (-1);
		}
	}

	return (0);
}

/**
 * _unsetenv - is function to unset or delete environment variable;
 * @name: name of variable;
 *
 * Return: value 0 for success otherwise -1.
 */
int _unsetenv(const char *name)
{
	char **current = environ, **nextvar;
	char *envar = _getenv(name);
	size_t nlen = strlen(name);

	if (envar == NULL)
		return (0);

	while (*current)
	{
		if (strncmp(*current, name, nlen) == 0 && (*current)[nlen] == '=')
		{
			nextvar = current + 1;
			while (*nextvar != NULL)
			{
				*current = *nextvar;
				++current;
				++nextvar;
			}
			*current = NULL;
			return (0);
		}
		++current;
	}

	perror("unset");
	return (-1);
}
