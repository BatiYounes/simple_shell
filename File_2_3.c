#include "main.h"

/**
 * home_dir - Change the current directory to the home directory.
 * @sh: Shell structure.
 *
 * Return: nothing.
 */
void home_dir(myshell *sh)
{
	char current_dir[PATH_MAX];
	char *_hdir = get_cd_env("HOME", sh->_env);

	getcwd(current_dir, sizeof(current_dir));
	if (_hdir == NULL || chdir(_hdir) == -1)
		handle_errors(sh, 2);
	else
	{
		set_cd("OLDPWD", current_dir, sh);
		set_cd("PWD", _hdir, sh);
	}
	sh->status = 0;
}

/**
 * *builtins - Get the pointer to the specified builtin command.
 * @command: The command entered by the user.
 *
 * Return: Pointer to the corresponding builtin function.
 */
int (*builtins(char *command))(myshell *)
{
	int k = 0, c;

	mybuiltins builtins[] = {
		{"exit", shell_exit},
		{"env", print_env_var},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", change_directory},
		{NULL, NULL},
	};
	while (builtins[k].name)
	{
		c = compare_strings(builtins[k].name, command);
		if (c == 0)
			break;
		k++;
	};
	return (builtins[k].function);
}

/**
 * shell_exit - Exit the shell prompt.
 * @sh: Shell structure.
 *
 * Return: 0 on success, 1 on failure.
 */
int shell_exit(myshell *sh)
{
	unsigned int st;
	int valid, length, num, should_exit;

	if (sh->args[1] != NULL)
		should_exit = 1;
	else
		should_exit = 0;
	if (should_exit)
	{
		valid = is_digit(sh->args[1]);
		st = string_to_integer(sh->args[1]);
		length = string_length(sh->args[1]);
		num = st > (unsigned int)INT_MAX;
		if (length > 10 || num || !valid)
		{
			handle_errors(sh, 2);
			sh->status = 2;
			return (1);
		}
		sh->status = (st % 256);
	}
	return (0);
}
