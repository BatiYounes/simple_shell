#include "main.h"

/**
 * find_execommand - Find and execute a command.
 * @sh: Shell structure.
 *
 * Return: 1 on success.
 */

int find_execommand(myshell *sh)
{
	int (*builtin_func)(myshell *sh);

	if (sh->args[0] == NULL)
		return (1);
	builtin_func = builtins(sh->args[0]);
	if (builtin_func != NULL)
		return (builtin_func(sh));
	return (execute_command(sh));
}
