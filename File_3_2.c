#include "main.h"

/**
 * set_cd - Set an environment variable for cd function.
 * @var_name: Environment variable name (e.g., pwd, oldpwd, home).
 * @var_value: Environment variable value.
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */

void set_cd(char *var_name, char *var_value, myshell *sh)
{
	char *evar, *ename;
	int i = 0, cmp;

	while (sh->_env[i])
	{
		evar = duplicate_string(sh->_env[i]);
		ename = tokenize_string(evar, "=");
		cmp = compare_strings(ename, var_name);
		if (cmp == 0)
		{
			free(sh->_env[i]);
			sh->_env[i] = create_env_var(ename, var_value);
			free(evar);
			return;
		}
		free(evar);
		i++;
	}
	sh->_env = reallocate_dp(sh->_env, i, (i + 2) * sizeof(char *));
	sh->_env[i] = create_env_var(var_name, var_value);
	sh->_env[i + 1] = NULL;
}
