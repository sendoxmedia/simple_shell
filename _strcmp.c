#include "header.h"
/**
 * _strncmp - Compares first character of two strings
 * str1 and str2.
 *
 * @str1: A pointer to the first input string.
 * @str2: A pointer to the second input string.
 * @n: An unsigned integer representing the maximum
 * number of characters to compare.
 *
 * Return: 0 if the first n characters of str1
 * and str2 are identical.
 * A non-zero value indicating the difference
 * between the two strings if they are not equal.
 */

unsigned int _strncmp(char *str1, char *str2, unsigned int n)
{
	unsigned int i = 0;

	if (_strlen(str1) < n || _strlen(str2) < n)
		return (1);

	while (i < n)
	{
		if (str1[i] != str2[i])
			return (1);

		i++;
	}

	return (0);
}
