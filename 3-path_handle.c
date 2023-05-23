#include "shell.h"

/**
 * _which - is function to find file path;
 * @filename: is a file to be used;
 *
 * Return: filepath otherwise NULL if not found.
 */
char *_which(const char *filename)
{
	const char *path;
	char *pathcp, *filepath, *dir;

	if (access(filename, F_OK) == 0)
		return (strdup(filename));

	filepath = malloc(SIZE);
	path = _getenv("PATH");
	pathcp = strdup(path);
	dir = custom_strtok(pathcp, ":");

	while (dir)
	{
		snprintf(filepath, SIZE, "%s/%s", dir, filename);
		if (access(filepath, F_OK) == 0)
		{
			free(pathcp);
			return (filepath);
		}
		dir = custom_strtok(NULL, ":");
	}

	free(filepath);
	free(pathcp);

	return (NULL);
}
