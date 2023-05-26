#include "shell.h"

/**
 * input_buffer - Read input from the user into a buffer.
 * @infoma: Pointer to the `infto_t` struct.
 * @the_buffer: Double pointer to the input buffer.
 * @length: Pointer to the size of the input buffer.
 *
 * Return:
 *   - The number of characters read (r) if successful.
 *   - 0 if the buffer size is not 0.
 */
ssize_t input_buffer(infto_t *infoma, char **the_buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*the_buffer); /*Free the existing buffer*/
		/*Set the_buffer to NULL to avoid using a dangling pointer*/
		*the_buffer = NULL;
		signal(SIGINT, sigintHandler); /*Set up the SIGINT signal handler*/
#if GET_LINE
		r = getline(the_buffer, &len_p, stdin);
#else
		r = custom_getline(infoma, the_buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*the_buffer)[r - 1] == '\n')
			{
				/*Remove the newline character from the input line*/
				(*the_buffer)[r - 1] = '\0';
				r--; /*Decrement the number of characters read*/
			}
			/*Set the countline_flag to indicate a new command line*/
			infoma->countline_flag = 1;
			rm_comment(*the_buffer); /*Remove comments from the input line*/
			/*Add the command to the history list*/
			build_histls(infoma, *the_buffer, infoma->count_hist++);
			/*Renumber the history list*/
			*length = r;
			infoma->bf_cmd = the_buffer;
		}
	}
	return (r);
}

/**
 * get_the_input - Get the input from the user and process it.
 * @infoma: Pointer to the `infto_t` struct.
 *
 * Return:
 *   - The length of the input if successful.
 *   - -1 if an error occurred during input.
 */
ssize_t get_the_input(infto_t *infoma)
{
	static char *the_buffer;
	static size_t i, j, length;
	ssize_t read_char = 0;
	char **the_buffer_p = &(infoma->arg), *pt;

	custom_putchar(BFLUSH); /*Flush the output buffer*/
	/*Read input into a buffer*/
	read_char = input_buffer(infoma, &the_buffer, &length);
	if (read_char == -1)
		return (-1);
	if (length)
	{
		j = i;
		pt = the_buffer + i;

		/*Check for chained commands and update j accordingly*/
		chain_checker(infoma, the_buffer, &j, i, length);
		while (j < length)
		{
			/*Check if a chain operator is found*/
			if (_ischain(infoma, the_buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0; /*Reset the buffer indices and length*/
			/*Set the command buffer type to normal command*/
			infoma->cmdbf_type = NORM_CMD;
		}

		/*Update the input buffer pointer in infoma struct*/
		*the_buffer_p = pt;
		return (_strlen(pt)); /*Return the length of the input*/
	}

	*the_buffer_p = the_buffer; /*Store the buffer in infoma->arg*/
	return (read_char);			/*Return the number of characters read*/
}

/**
 * buffer_reader - Read data into a buffer from a file descriptor.
 * @infoma: Pointer to the `infto_t` struct.
 * @buf: Pointer to the buffer for storing the read data.
 * @i: Pointer to the index of the buffer.
 *
 * Return:
 *   - The number of bytes read (r) if successful.
 *   - 0 if the index i is non-zero.
 *   - -1 if an error occurred during the read operation.
 */
ssize_t buffer_reader(infto_t *infoma, char *buf, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
		return (0);

	/*Read data from the file descriptor into the buffer*/
	read_bytes = read(infoma->readfd, buf, RD_BSIZE);
	if (read_bytes >= 0)
		*i = read_bytes; /*Update the index of the buffer*/
	return (read_bytes);
}

/**
 * custom_getline - Read a line of input from a file descriptor.
 * @infoma: Pointer to the `infto_t` struct.
 * @ptr: Pointer to the buffer for storing the line of input.
 * @length: Pointer to the length of the buffer.
 *
 * Return:
 *   - The new length of the buffer (s) if successful.
 *   - -1 if an error occurred during the read operation.
 */
int custom_getline(infto_t *infoma, char **ptr, size_t *length)
{
	static char buffs[RD_BSIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *pt = NULL, *new_p = NULL, *char_search;

	pt = *ptr; /*Current buffer*/
	if (pt && length)
		s = *length;
	if (i == len)
		i = len = 0; /*If position and length are equal, reset them*/

	r = buffer_reader(infoma, buffs, &len); /*Read data into the buffer*/
	if (r == -1 || (r == 0 && len == 0))
		return (-1); /*Return -1 if an error occurred during the read*/
	/*Search for newline character*/
	char_search = custom_strchr(buffs + i, '\n');
	/*Determine length of the line*/
	k = char_search ? 1 + (unsigned int)(char_search - buffs) : len;
	/* Reallocate buffer for the new line */
	new_p = custom_realloc(pt, s, s ? s + k : k + 1);
	if (!new_p)
		return (pt ? free(pt), -1 : -1); /*If reallocation fails, return -1*/
										 /*Copy read data to the new buffer*/
	if (s)
		custom_strncat(new_p, buffs + i, k - i);
	else
		custom_strncpy(new_p, buffs + i, k - i + 1);

	s += k - i; /*Update the length and position*/
	i = k;
	pt = new_p;

	if (length)
		*length = s; /*Update length if length pointer is provided*/
	*ptr = pt;
	return (s); /*Return new length of the buffer*/
}

/**
 * sigintHandler - Signal handler for SIGINT (Ctrl+C) signal.
 * @sig_num: The signal number (unused in the function).
 *
 * Return: Nothing
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	custom_putchar(BFLUSH);
}
