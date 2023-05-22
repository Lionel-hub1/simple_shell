#include "shell.h"

/**
 * _which - is function to find file path;
 * @filename: is a file to be used;
 *
 * Return: filepath otherwise NULL if not found.
 */
char *_which(const char *filename)
{
	char *filepath = malloc(SIZE);
	const char *path = _getenv("PATH");
	char *pathcp = strdup(path);
	char *dir = strtok(pathcp, ":");

	while (dir)
	{
		snprintf(filepath, SIZE, "%s/%s", dir, filename);
		if (access(filepath, F_OK) == 0)
		{
			free(pathcp);
			return (filepath);
		}
		dir = strtok(NULL, ":");
	}

	free(filepath);
	free(pathcp);

	return (NULL);
}
