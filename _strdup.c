#include "header.h"

/**
 * _strdup - Duplicates a string and returns a dynamically allocated copy.
 * Responsible for freeing the memory when it is no
 * longer needed.
 *
 * @str: A pointer to the null-terminated string to duplicate.
 *
 * Return: A pointer to a newly allocated duplicate of the input string,
 * or NULL if memory allocation fails.
 */
char *_strdup(char *str)
{
	unsigned int len = _strlen(str);
	unsigned int i;
	char *new_str = malloc(sizeof(char) * (len + 1));

	if (new_str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		new_str[i] = str[i];
	}

	new_str[i] = '\0';

	return (new_str);
}
