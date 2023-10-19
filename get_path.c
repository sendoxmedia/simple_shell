#include "header.h"
/**
 * get_path - This function takes an array of
 * environment variables (env) and retrieves
 * the value associated with the "PATH"
 * environment variable.
 *
 * @env: A pointer to an array of environment
 * variables, where the "PATH" variable is to be
 * retrieved.
 *
 * Return: A pointer to a character string (char*):
 * The value of the PATH environment variable,
 * which consists of a colon-separated list of
 * directory paths.
 */

char *get_path(char **env)
{
	unsigned int j = 0;
	char *path;

	while (env[j] != NULL)
	{
		if (_strncmp("PATH", env[j], 4) == 0)
		{
			path = _strdup(env[j]);

			if (path == NULL)
				break;

			return (path);
		}

		j++;
	}

	return (NULL);
}
