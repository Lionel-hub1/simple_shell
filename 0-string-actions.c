#include "shell.h"

/**
 * _strlen - This function calculates the size of a string
 * @str: is the string to be calculated
 *
 * Return: integer length of string
 */
int _strlen(char *str)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str++)
		count++;
	return (count);
}

/**
 * custom_strcmp - This function compares two strings
 * @str1: Is the first string
 * @str2: Is the second string
 *
 * Return: integer difference between strings
 */
int custom_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		/* Compare characters of 'str1' and 'str2' */
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	/* Check for equality after the loop */
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - This function check if a string starts with a specific
 * substring
 *
 * @haystack: Is the string to search within
 * @needle: Is the substring to search for
 *
 * Return: pointer to the start of the substring or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 **custom_strncat - This function is a custom implementation of strncat
 *@dest: Is the first string
 *@src: Is the second string
 *@bytes: Is the number of bytes to concatenate
 *Return: (s) a pointer to the memory area s
 */
char *custom_strncat(char *dest, char *src, int bytes)
{
	int i = 0, j = 0;
	char *s = dest;

	/* Find the length of the destination string */
	while (dest[i] != '\0')
		i++;

	/* Append characters from 'src' to 'dest' until 'bytes' limit */
	while (src[j] != '\0' && j < bytes)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* Add null terminator if the number of appended characters < 'bytes' */
	if (j < bytes)
		dest[i] = '\0';
	return (s);
}

/**
 * custom_strchr - Locates the first occurrence of a character in a string.
 * @str: The string to be searched.
 * @c: The character to be located.
 *
 * Return: Pointer to the first occurrence of the character 'c' in the
 *         string 'str', or NULL if the character is not found.
 */
char *custom_strchr(char *str, char c)
{
	/* Loop through the string until the end or until character 'c' is found */
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
