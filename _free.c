#include "header.h"
/**
 * _free -  function used for deallocating memory
 * associated with one or more pointers. This function
 * takes three arguments
 *
 * @lineptr: A pointer to a character array (char *)
 * that typically holds a string or memory that needs
 * to be freed.
 *
 * @command: A pointer to a pointer to characters
 * (char **) often used to store an array of
 * strings or command-related data that should be
 * deallocated.
 *
 * @free_command_0: An unsigned integer used as a flag or
 * indicator.
 */

void _free(char *lineptr, char **command, unsigned int free_command_0)
{
	free(lineptr);

	if (free_command_0 == COMMAND_VALIDATED)
		free(command[0]);

	free(command);
}
