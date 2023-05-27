#include "shell.h"

/**
 * file_history - a function to find file history;
 * @infoma: is informant structure;
 *
 * Return: file's history in form of string.
 */

char *file_history(infto_t *infoma)
{
	char *buffer, *dir;

	dir = environ_getter(infoma, "HOME=");
	if (dir == NULL)
		return (NULL);

	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(FILE_HIST) + 2));
	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	custom_strcpy(buffer, dir);
	custom_strcat(buffer, "/");
	custom_strcat(buffer, FILE_HIST);

	return (buffer);
}

/**
 * wr_history - is a function to create or append history of a file;
 * @infoma: is informant of inft_t structure;
 *
 * Return: value 1 for success otherwise -1;
 */
int wr_history(infto_t *infoma)
{
	char *file_hist = file_history(infoma);
	ssize_t fdc;
	strl_t *node = NULL;

	if (!file_hist)
		return (-1);

	fdc = open(file_hist, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_hist);
	if (fdc == -1)
		return (-1);

	node = infoma->history;
	while (node)
	{
		custom_putsfd(node->str, fdc);
		custom_put_filedescriptor('\n', fdc);
		node = node->next;
	}
	custom_put_filedescriptor(BFLUSH, fdc);
	close(fdc);

	return (1);
}

/**
 * rd_history - is a function to read the file history;
 * @infoma: is informant of infto_t structure;
 *
 * Return: counts of history's file otherwise 0;
 */
int rd_history(infto_t *infoma)
{
	int i, last = 0, linecounts = 0;
	ssize_t fdc, len, fsize = 0;
	struct stat st;
	char *buffer = NULL, *file_hist = file_history(infoma);

	if (!file_hist)
		return (0);
	fdc = open(file_hist, O_RDONLY);
	free(file_hist);
	if (fdc == -1)
		return (0);
	if (!fstat(fdc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	len = read(fdc, buffer, fsize);
	buffer[fsize] = 0;
	if (len <= 0)
		return (free(buffer), 0);
	close(fdc);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_histls(infoma, buffer + last, linecounts++);
			last = i + 1;
		}
	if (last != i)
		build_histls(infoma, buffer + last, linecounts++);
	free(buffer);
	infoma->count_hist = linecounts;
	while (infoma->count_hist-- >= MAX_HIST)
		del_nodeidx(&(infoma->history), 0);
	renum_hist(infoma);

	return (infoma->count_hist);
}

/**
 * build_histls - is a function to add entry of linked list;
 * @infoma: is a structure informant for infto_t struct;
 * @buffer: is a buffer of string;
 * @linecounts: history counts from count_hist;
 *
 * Return: value 0 for sucess;
 */
int build_histls(infto_t *infoma, char *buffer, int linecounts)
{
	strl_t *node = NULL;

	if (infoma->history)
		node = infoma->history;

	end_addnode(&node, buffer, linecounts);

	if (!infoma->history)
		infoma->history = node;

	return (0);
}

/**
 * renum_hist - is a func to renumber file history after chages;
 * @infoma: is a structure informant for infto_t struct;
 *
 * Return: history counts from count_hist;
 */
int renum_hist(infto_t *infoma)
{
	strl_t *node = infoma->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}

	return (infoma->count_hist = x);
}
