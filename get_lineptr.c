#include "header.h"
/**
 * get_lineptr is a function that doesn't take any
 * arguments and is responsible for obtaining a
 * line or string input from a data source, often 
 * standard input or a file.
 *
 * Return: (lineptr)
 */

char *get_lineptr(void)
{
	char *lineptr = NULL;
	size_t n = 0;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);

	if (getline(&lineptr, &n, stdin) == -1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "\nexit\n", 6);

		free(lineptr);
		return (NULL);
	}

	if (_strncmp(lineptr, "exit", 4) == 0)
	{
		free(lineptr);
		return (NULL);
	}

	return (lineptr);
}
