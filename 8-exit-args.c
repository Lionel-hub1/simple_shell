#include "shell.h"
/**
 * str_to_int - This function convert strings to int.
 * @str: Is The input string
 * Return: The converted integer value, or -1 if conversion fails.
 */
int str_to_int(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	/* check for NULL pointer */
	if (*str == '+')
		str++;

	/*Count the number of words in string*/
	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;				  /* Multiply the current result by 10 */
			result += (str[index] - '0'); /* Add the digit to the result */
			if (result > INT_MAX)
				return (-1); /* Overflow check */
		}
		else
			return (-1); /* Invalid character found, return -1 */
	}
	return (result);
}
