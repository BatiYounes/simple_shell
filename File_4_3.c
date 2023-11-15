#include "main.h"

/**
 * path_error - Generate an error message for path_error.
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *path_error(myshell *sh)
{
	char *error, *s = integer_to_string(sh->line_count);
	int l = string_length(sh->av[0]) + string_length(s);

	l = l + string_length(sh->args[0]) + 25;

	error = malloc((l + 1) * sizeof(char));
	if (error == 0)
	{
		free(error);
		free(s);
		return (NULL);
	}

	copy_string(error, sh->av[0]);
	concatenate_strings(error, ": ");
	concatenate_strings(error, s);
	concatenate_strings(error, ": ");
	concatenate_strings(error, sh->args[0]);
	concatenate_strings(error, ": Permission denied\n");
	concatenate_strings(error, "\0");
	free(s);

	return (error);
}
