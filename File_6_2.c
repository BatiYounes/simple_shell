#include "main.h"

/**
 * string_length - Get the length of a string.
 * @str: Pointer to a string of characters.
 *
 * Return: Length of the string.
 */

int string_length(const char *str)
{
	int str_length = 0;

	while (str[str_length] != '\0')
		str_length++;
	return (str_length);
}
