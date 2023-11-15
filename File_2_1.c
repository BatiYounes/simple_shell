#include "main.h"

/**
 * change_directory - Change the current directory.
 * @sh: Shell structure.
 *
 * Return: Always 1 (success).
 */

int change_directory(myshell *sh)
{
	char *d = sh->args[1];

	if (d == NULL || compare_strings(d, "$HOME") == 0
			|| compare_strings(d, "--") == 0)
	{
		home_dir(sh);
		return (1);
	}
	else if (compare_strings(d, "-") == 0)
	{
		previous_dir(sh);
		return (1);
	}
	cd(sh);
	return (1);
}
