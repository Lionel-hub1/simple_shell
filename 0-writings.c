#include "shell.h"

/**
 * print_decimals - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @file_d: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimals(int input, int file_d)
{
	int (*__putchar)(char) = custom_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file_d == STDERR_FILENO)
		__putchar = custom_error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i); /* Print the digit */
			count++;
		}
		current %= i; /* Update the current value */
	}
	__putchar('0' + current); /* Print the last digit */
	count++;

	return (count);
}

/**
 * custom_putchar - Writes a character to the standard output.
 * @c: The character to be written.
 *
 * Return: 1 on success.
 */
int custom_putchar(char c)
{
	static int index;
	static char buffer[WR_BSIZE];

	if (c == BFLUSH || index >= WR_BSIZE)
	{
		/* Flush the buffer */
		write(1, buffer, index);
		index = 0;
	}
	/* Store the character in the buffer */
	if (c != BFLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * custom_error_putchar - this function prints a character to the
 * standard error.
 *
 * @c: The character to be written.
 *
 * Return: 1 on success.
 */
int custom_error_putchar(char c)
{
	static int index;
	static char buf[WR_BSIZE];

	if (c == BFLUSH || index >= WR_BSIZE)
	{
		write(2, buf, index); /* Flush the buffer */
		index = 0;
	}
	/* Store the character in the buffer */
	if (c != BFLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * custom_put_filedescriptor - Writes character to a specified file descriptor
 * @c: The character to be written.
 * @fdcr: The file descriptor to write the character to.
 *
 * Return: 1 on success.
 */
int custom_put_filedescriptor(char c, int fdcr)
{
	static int i;
	static char buf[WR_BSIZE];

	if (c == BFLUSH || i >= WR_BSIZE)
	{
		write(fdcr, buf, i); /* Flush the buffer to stderr */
		i = 0;
	}
	/* Store the character in the buffer */
	if (c != BFLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * custom_putsfd - Writes a string to a specified file descriptor.
 * @str: The string to be written.
 * @fdcr: The file descriptor to write the string to.
 *
 * Return: The number of characters written on success, 0 if @str is NULL.
 */
int custom_putsfd(char *str, int fdcr)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		/* Write each character to the specified file descriptor */
		i += custom_put_filedescriptor(*str++, fdcr);
	}
	return (i);
}
