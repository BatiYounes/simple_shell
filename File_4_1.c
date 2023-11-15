#include "main.h"

/**
 * cd_error - Print an error message for change directory error
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *cd_error(myshell *sh)
{
	char *error, *message, *s = integer_to_string(sh->line_count);
	int id, l;

	if (sh->args[1][0] == '-')
	{
		message = ": Not a legal option ";
		id = 2;
	}
	else
	{
		message = ": can't cd to given directory ";
		id = string_length(sh->args[1]);
	}

	l = string_length(sh->av[0]) + string_length(sh->args[0]);
	l = l + string_length(s) + string_length(message) + id + 6;

	error = malloc((l + 1) * sizeof(char));
	if (error == 0)
	{
		free(s);
		return (NULL);
	}

	error = cd_error_concat(sh, message, error, s);
	free(s);

	return (error);
}
