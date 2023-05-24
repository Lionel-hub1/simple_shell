#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_string - Prints a string to stdout.
 * @str: The string to be printed.
 *
 * Return: void
 */
void print_string(char *str)
{
	int i;

	if (!str)
		return;

	i = 0;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * custom_snprintf - Write formatted output to a string.
 * @str: Pointer to the destination string.
 * @size: The size of the destination string.
 * @format: The format string.
 * @...: The variadic arguments.
 *
 * Return: The number of characters written (excluding the null byte used to
 * 	   end output to strings), or a negative value if an output error
 * 	   occurs.
 */
int custom_snprintf(char *str, size_t size, const char *format, ...)
{
	int written = 0;
	va_list args;
	va_start(args, format);

	/* Check for NULL pointer or zero size */
	if (str == NULL || size == 0)
	{
		va_end(args);
		return -1;
	}

	/* Iterate over the format string */
	for (; *format != '\0'; ++format)
	{
		/* Check if there is enough space in destination string */
		if (written < (int)size - 1)
		{
			*str++ = *format;
			++written;
		}
		else
		{
			break;
		}
	}

	/* Null-terminate the destination string */
	*str = '\0';

	va_end(args);
	return written;
}
