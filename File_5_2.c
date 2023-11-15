#include "main.h"

/**
 * toke_commandl - Tokenize the input string into command line arguments.
 * @user_input: Input string.
 *
 * Return: Parsed command line arguments.
 */
char **toke_commandl(char *user_input)
{
	char **parsed_t;
	char *token;
	size_t i, buffer_size = 128;

	parsed_t = malloc((buffer_size) * sizeof(char *));
	if (parsed_t == NULL)
	{
		exit(EXIT_FAILURE);
	}

	token = tokenize_string(user_input, " \t\r\n\a");
	parsed_t[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size = buffer_size + buffer_size;
			parsed_t = reallocate_dp(parsed_t, i, sizeof(char *));
			if (parsed_t == NULL)
			{
				exit(EXIT_FAILURE);
			}
		}

		token = tokenize_string(NULL, " \t\r\n\a");
		parsed_t[i] = token;
	}

	return (parsed_t);
}
