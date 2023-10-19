#include "header.h"

/**
 * _strlen - Calculate the length of a null-terminated string.
 *
 * @str: A pointer to the null-terminated string to measure.
 *
 * Return: The length of the input string as an unsigned integer.
 */
unsigned int _strlen(char *str)
{
	unsigned int len = 0;

	for (; str[len] != '\0'; len++)
		;

	return (len);
}
