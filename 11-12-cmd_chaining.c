#include "shell.h"

/**
 * chain_checker - is a function for checking
 * continous chaining by on last status;
 * @infoma: is informant structure of infto_t struct parameter;
 * @buffer: is a buffer to be used;
 * @pt: is a pointer to the current index of buffer to be used;
 * @i: is index at starting point in buffer to be used;
 * @len: is a length size of buffer to be used;
 *
 * Return: nothing;
 */
void chain_checker(infto_t *infoma, char *buffer,
				size_t *pt, size_t i, size_t len)
{
	size_t y = *pt;

	if (infoma->cmdbf_type == AND_CMD)
	{
		if (infoma->status)
		{
			buffer[i] = 0;
			y = len;/* equalizing current to the length at last */
		}
	}

	if (infoma->cmdbf_type == OR_CMD)
	{
		if (!infoma->status)
		{
			buffer[i] = 0;
			y = len;/* equalizing current to the length at last */
		}
	}

	*pt = y;
}

/**
 * _ischain - is a function to check if a char is a chain delim;
 * @infoma: is informant structure of infto_t struct parameter;
 * @buffer: is a buffer to be used;
 * @pt: is a pointer to the current index of buffer to be used;
 *
 * Return: value 1 if it is chain delimeter otherwise 0 for false.
 */
int _ischain(infto_t *infoma, char *buffer, size_t *pt)
{
	size_t y = *pt;

	if (buffer[y] == '|' && buffer[y + 1] == '|')
	{
		buffer[y] = 0; /* if found at the end of command increement */
		y++;

		infoma->cmdbf_type = OR_CMD; /* for choosing one of cmd */
	}
	else if (buffer[y] == '&' && buffer[y + 1] == '&')
	{
		buffer[y] = 0; /* if found at the end of command increement */
		y++;

		infoma->cmdbf_type = AND_CMD; /* for adding new command */
	}
	else if (buffer[y] == ';') /* if found at the end of command */
	{
		buffer[y] = 0; /* will be replaced by null at cmd line */
		infoma->cmdbf_type = CHAIN_CMD;
	}
	else
		return (0);
	*pt = y;

	return (1);
}
