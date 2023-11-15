#include "main.h"

/**
 * count_digits - Count the number of digits in an integer.
 * @num: Input integer.
 *
 * Return: Number of digits in the integer.
 */

int count_digits(int num)
{
	int digit_count = 1;
	unsigned int absolute_num;

	if (num < 0)
	{
		digit_count++;
		absolute_num = num * -1;
	}
	else
		absolute_num = num;
	while (absolute_num > 9)
	{
		digit_count++;
		absolute_num = absolute_num / 10;
	}

	return (digit_count);
}

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
