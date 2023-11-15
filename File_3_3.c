#include "main.h"

/**
 * cd - Change the current directory
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */

void cd(myshell *sh)
{
	char *dir, *p, *c;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	dir = sh->args[1];
	if (chdir(dir) == -1)
	{
		handle_errors(sh, 2);
		return;
	}
	p = duplicate_string(pwd);
	set_cd("OLDPWD", p, sh);
	c = duplicate_string(dir);
	set_cd("PWD", c, sh);
	free(p);
	free(c);
	sh->status = 0;
	chdir(dir);
}

/**
 * get_cd_env - Get an environment variable for cd.
 * @var_name: Name of the environment variable.
 * @_env: Environment variable array.
 *
 * Return: Environment variable value, or NULL if not found.
 */

char *get_cd_env(const char *var_name, char **_env)
{
	char *e = NULL;
	int i = 0, j = 0;

	while (_env[i])
	{
		j = compare_env_varname(_env[i], var_name);
		if (j)
		{
			e = _env[i];
			break;
		}
		i++;
	}
	return (e + j);
}
