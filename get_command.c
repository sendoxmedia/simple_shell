#include "header.h"
/**
 *@ get_command is a C function that takes a single argument,
 * a pointer to a character array lineptr
 *
 * Return: (command)
 */

char **get_command(char *lineptr)
{
	char **command;
	unsigned int args, i = 0;

	args = get_args(lineptr);
	command = malloc(sizeof(char *) * (args + 1));

	if (command == NULL)
		return (NULL);

	command[i] = strtok(lineptr, " \n\t\r");

	while (command[i] != NULL)
	{
		i++;
		command[i] = strtok(NULL, " \n\t\r");
	}

	return (command);
}
