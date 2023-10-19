#include "header.h"
/**
 * build_path - This function takes two input strings,
 * dir (directory) and file (file), and combines them
 * to create a complete file path.
 *
 * @dir - A pointer to the directory portion of the path.
 * @file - A pointer to the filename or file portion of
 * the path.
 *
 * Return: A pointer to a character string (char*):
 * The resulting file path created by concatenating dir and file.
 */

char *build_path(char *dir, char *file)
{
	int i = 0, j = 0;
	unsigned int len = _strlen(dir) + _strlen(file) + 2;
	char *full_path = malloc(sizeof(char) * len);

	if (full_path == NULL)
		return (NULL);

	while (dir[i] != '\0')
	{
		full_path[j] = dir[i];
		i++, j++;
	}

	full_path[j] = '/';
	i = 0;
	j++;

	while (file[i] != '\0')
	{
		full_path[j] = file[i];
		i++, j++;
	}

	full_path[j] = '\0';

	return (full_path);
}
