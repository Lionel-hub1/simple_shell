#include "shell.h"

/**
 * str_to_words - Convert a string into an array of words using delimiters.
 * @str: The input string to be split into words.
 * @delimiters: The delimiters used to split the string into words (optional).
 *
 * Return: Array of strings representing the words, or NULL if no words found
 */

char **str_to_words(char *str, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (i = 0; str[i] != '\0'; i++) /*Count the number of words in string*/
		if (!is_delimeter(str[i], delimiters) &&
			(is_delimeter(str[i + 1], delimiters) ||
			 !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *)); /*Alloc memry for arr*/
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++) /* Split the string into words */
	{
		while (is_delimeter(str[i], delimiters)) /* Skip delimiters */
			i++;
		k = 0; /* Count the number of characters in the word */
		while (!is_delimeter(str[i + k], delimiters) && str[i + k])
			k++;
		words[j] = malloc((k + 1) * sizeof(char)); /*Alloc memory for word*/
		if (!words[j])
		{ /* Free all previously allocated memory */
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = str[i++]; /* Copy the word into the array */
		words[j][m] = 0;
	}
	words[j] = NULL; /* Set the last element of the array to NULL */
	return (words);
}

/**
 * free_buffer - Free memory allocated for a pointer and set it to NULL
 * @ptr: A pointer to the memory to be freed
 *
 * Return: 1 if memory was freed successfully, 0 otherwise
 */
int free_buffer(void **ptr)
{
	/* Check if pointer is not NULL and points to a valid address */
	if (ptr && *ptr)
	{
		free(*ptr);	 /* Free memory */
		*ptr = NULL; /* Set pointer to NULL after freeing */
		return (1);
	}
	return (0);
}

/**
 * custom_itoa - Convert a long integer to a string representation.
 * @num: The long integer to be converted.
 * @base: The base for the conversion (e.g., 10 for decimal).
 * @flags: Flags for customizing the conversion behavior.
 *
 * Return: A pointer to the string representation of the long integer.
 */
char *custom_itoa(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0; /* Flag for negative numbers */
	char *ptr;
	unsigned long n = (unsigned long)num;

	/* If number is zero, return a string of zero */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	/* Set the default base to 10 if not specified */
	array = flags & CONVTO_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base]; /* Convert the number to string */
		n /= base;				  /* Update the number to be converted */
	} while (n != 0);

	if (sign)
		*--ptr = sign; /* Add the negative sign if necessary */
	return (ptr);
}
