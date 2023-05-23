#include "shell.h"

/**
 * custom_strtok - Tokenizes a string using specified delimiters
 * @str: The string to be tokenized
 * @delimiters: The delimiters used for tokenization
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found.
 */
char *custom_strtok(char *str, const char *delimiters)
{
	static char *lastToken = '\0';
	char *token;

	/* If a new string is provided, update the last token */
	if (str != NULL)
		lastToken = str;

	/* If the last token is NULL, there are no more tokens */
	if (lastToken == NULL)
		return (NULL);

	/* Skip leading delimiters */
	while (*lastToken != '\0' && strchr(delimiters, *lastToken) != NULL)
		lastToken++;

	/* If the last token is empty, there are no more tokens */
	if (*lastToken == '\0')
		return (NULL);

	/* Find the end of the current token */
	token = lastToken;

	while (*lastToken != '\0' && strchr(delimiters, *lastToken) == NULL)
		lastToken++;

	/* If the end of the string is reached, update the last token to NULL */
	if (*lastToken == '\0')
		lastToken = NULL;
	else
		*lastToken++ = '\0'; /* Replace delimiter with NULL character */

	return (token);
}
