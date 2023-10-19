#include "header.h"

/**
 * get_args - Extracts and returns an unsigned integer from a given string.
 *
 * @str: A pointer to the input string to parse.
 *
 * Return: 0 if no valid integer is found.
 */
unsigned int get_args(char *str)
{
	unsigned int args = 0;
	char *new_str = _strdup(str);
	char *token;

	token = strtok(new_str, " \n\t\r");

	while (token != NULL)
	{
		token = strtok(NULL, " \n\t\r");
		args++;
	}

	free(new_str);

	return (args);
}
