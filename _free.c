#include "header.h"
/**
 * @free_command_0 - Frees memory associated with a dynamically
 * allocated 'lineptr' and, optionally, the first element of
 * 'command' based on the 'free_command_0' flag.
 */

void _free(char *lineptr, char **command, unsigned int free_command_0)
{
	free(lineptr);

	if (free_command_0 == COMMAND_VALIDATED)
		free(command[0]);

	free(command);
}
