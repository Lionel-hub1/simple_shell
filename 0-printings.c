#include "shell.h"

/**
 * print_string - This function prints a string to standard output
 * @str: The string to be printed
 * Return: void
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_error_putchar(str[index]);
		index++;
	}
}

/**
 * print_linked_list - This function prints a linked list of strings
 * @head: Is the pointer to the head of the linked list
 *
 * Return: The number of nodes in the linked list
 */
size_t print_linked_list(const strl_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * print_ls - This function prints a linked list of structures
 * @head: Is a pointer to the head of the linked list
 *
 * Return: The number of nodes in the linked list
 */
size_t print_ls(const strl_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(custom_itoa(head->num, 10, 0));
		custom_putchar(':');
		custom_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * _puts - This function prints a string to standard output
 * @str: Is the sting to print
 *
 * Return: void
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_putchar(str[index]);
		index++;
	}
}
