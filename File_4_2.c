#include "main.h"

/**
 * cd_error_concat - Concatenate the error message for cd_error.
 * @sh: Shell structure.
 * @message: Message to show to the user.
 * @error: Output message.
 * @line: Line of string.
 *
 * Return: Error message.
 */
char *cd_error_concat(myshell *sh, char *message, char *error, char *line)
{
	char *i;

	copy_string(error, sh->av[0]);
	concatenate_strings(error, ": ");
	concatenate_strings(error, line);
	concatenate_strings(error, ": ");
	concatenate_strings(error, sh->args[0]);
	concatenate_strings(error, message);

	if (sh->args[1][0] == '-')
	{
		i = malloc(3);
		i[0] = '-';
		i[1] = sh->args[1][1];
		i[2] = '\0';
		concatenate_strings(error, i);
		free(i);
	}
	else
	{
		concatenate_strings(error, sh->args[1]);
	}

	concatenate_strings(error, "\n");
	concatenate_strings(error, "\0");
	return (error);
}
