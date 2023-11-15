#include "main.h"


/**
 * previous_dir - Change the current directory to the previous directory.
 * @sh: Shell structure.
 *
 * Return: nothing.
 */
void previous_dir(myshell *sh)
{
	char *current_dir, *old_dir, *current_pwd, *old_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	current_pwd = duplicate_string(pwd);
	old_dir = get_cd_env("OLDPWD", sh->_env);

	if (old_dir == NULL)
		old_pwd = current_pwd;
	else
		old_pwd = duplicate_string(old_dir);
	set_cd("OLDPWD", current_pwd, sh);
	switch (chdir(old_pwd))
	{
		case -1:
			set_cd("PWD", current_pwd, sh);
			break;
		default:
			set_cd("PWD", old_pwd, sh);
	}
	current_dir = get_cd_env("PWD", sh->_env);
	write(STDOUT_FILENO, current_dir, string_length(current_dir));
	write(STDOUT_FILENO, "\n", 1);
	free(current_pwd);
	if (old_dir)
		free(old_pwd);
	sh->status = 0;
	chdir(current_dir);
}
