#include "shell.h"

/**
 * custom_strcat - concatenates two strings
 * @dest: Is the destination string to which 'src' will be appended
 * @src: Is the source string containing the characters to be appended
 *
 * Return: Pointer to the resulting concatenated string
 */
char *custom_strcat(char *dest, char *src)
{
	char *ret = dest;

	/* Find the end of the destination string */
	while (*dest)
		dest++;

	/* Append characters from 'src' to 'dest' */
	while (*src)
		*dest++ = *src++;

	*dest = *src; /* Copy the null terminator */
	return (ret);
}

/**
 * custom_strcpy - This function copies a string from source to destination.
 * @dest: Is the destination string where 'src' will be copied to.
 * @src: Is the source string to be copied.
 *
 * Return: A pointer to the destination string
 */
char *custom_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);

	/* Copy characters from 'src' to 'dest' */
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	/* Add null terminator to the destination string */
	dest[index] = 0;
	return (dest);
}

/**
 * custom_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);

	/* Calculate the length of the string */
	while (*str++)
		length++;

	/* Allocate memory for the duplicate string */
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
		return (NULL);

	/* Copy the string in reverse order to the duplicate */
	for (length++; length--;)
		duplicate[length] = *--str;
	return (duplicate);
}

/**
 * custom_strncpy - This fn copies up to 'n' characters from source
 * to destination.
 *
 * @dest: Is the destination string where 'src' will be copied to.
 * @src: Is the source string to be copied.
 * @n: is the maximum number of characters to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * string_replacer - Replaces the content of a pointer to a string
 * with a new string.
 *
 * @old: Pointer to the old string to be replaced.
 * @new: The new string to replace the old string.
 *
 * Return: 1 upon successful replacement, 0 otherwise.
 */
int string_replacer(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
