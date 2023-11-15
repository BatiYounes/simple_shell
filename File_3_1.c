#include "main.h"

/**
 * compare_env_varname - Compare environment variable names.
 * @variable_name: Name of the environment variable.
 * @partial_name: Partial name to compare.
 *
 * Return: 0 if not equal, i + 1 if equal.
 */

int compare_env_varname(const char *variable_name, const char *partial_name)
{
	int i = 0;

	while (variable_name[i] != '=')
	{
		if (variable_name[i] != partial_name[i])
			return (0);
		i++;
	}
	return (i + 1);
}

/**
 * set_cd - Set an environment variable for cd function.
 * @var_name: Environment variable name (e.g., pwd, oldpwd, home).
 * @var_value: Environment variable value.
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */
