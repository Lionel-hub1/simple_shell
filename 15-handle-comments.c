#include "shell.h"


/**
 * rm_comment - is a function to remove comment
 * by replacing this '#' with '\0';
 * @buffer: is a buffer of a target string (comment);
 *
 * Return: value 0 for success.
 */
void rm_comment(char *buffer)
{
	int x;

	for (x = 0; buffer[x] != '\0'; x++)
		if (buffer[x] == '#' && (!x || buffer[x - 1] == ' '))
		{
			buffer[x] = '\0';
			break;
		}
}
