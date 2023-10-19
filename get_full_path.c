#include "header.h"
/**
 * get_full_path - This function takes two inputs,
 * file and env, and attempts to locate the full
 * path to the specified file within the environment
 * variables provided in env.
 *
 * @file - A pointer to the string representing the
 * file or executable to be located.
 * @env - A pointer to an array of environment
 * variables (as strings) that contain directory
 * paths to search for the specified file.
 *
 * Return: A pointer to a character string (char*):
 * The full path to the specified file if it is found
 * within one of the directories specified in env.
 * If the file is not found, the function may return NULL
 * or a special value to indicate the absence of the file.
 */

char *get_full_path(char *file, char **env, char *shell)
{
	char *path, *full_path, *dir;

	path = get_path(env);

	if (path == NULL)
	{
		write(2, shell, _strlen(shell));
		write(2, ": 1: ", 5);
		write(2, file, _strlen(file));
		write(2, ": not found\n", 12);
		return (NULL);
	}

	strtok(path, "=:");
	dir = strtok(NULL, "=:");

	while (dir != NULL)
	{
		full_path = build_path(dir, file);

		if (full_path == NULL)
			break;

		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, "=:");
	}

	print_error(shell, file);
	free(path);
	return (NULL);
}
