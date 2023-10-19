#include "header.h"
/**
 * print_error -  is a function designed to handle and display
 * error messages related to a shell or command execution.
 * It takes two arguments, both of type char *
 *
 * @shell: A pointer to a character array (char *) representing
 * the name or identifier of the shell or program where the error
 * occurred.
 * @command: A pointer to a character array (char *) representing
 * the specific command that triggered the error.
 */

void print_error(char *shell, char *command)
{
	char *line = ": line 1: ";
	unsigned int i, j, len = _strlen(shell) + _strlen(command) + 11;
	char *error_header = malloc(sizeof(char) * len);

	if (error_header == NULL)
		return;

	for (j = 0, i = 0; shell[i] != '\0'; i++, j++)
		error_header[j] = shell[i];

	for (i = 0; line[i] != '\0'; i++, j++)
		error_header[j] = line[i];

	for (i = 0; command[i] != '\0'; i++, j++)
		error_header[j] = command[i];

	error_header[j] = '\0';
	perror(error_header);
	free(error_header);
}
