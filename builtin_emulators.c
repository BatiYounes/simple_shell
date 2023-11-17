#include "shell.h"

/**
 * _exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exit(info_t *info)
{
	int checkexit;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		checkexit = erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			eputs(info->argv[1]);
			eputchar('\n');
			return (1);
		}
		info->err_num = erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cd(info_t *info)
{
	char *f, *_dir, _buffer[1024];
	int chdir;

	f = _cwd(_buffer, 1024);
	if (!f)
		put("TODO: >>_cwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		_dir = _env(info, "HOME=");
		if (!_dir)
			chdir = /* TODO: what should this be? */
				chdir((_dir = _env(info, "PWD=")) ? _dir : "/");
		else
			chdir = chdir(_dir);
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		if (!_env(info, "OLDPWD="))
		{
			put(s);
			putchar('\n');
			return (1);
		}
		put(_env(info, "OLDPWD=")), putchar('\n');
		chdir = /* TODO: what should this be? */
			chdir((dir = _env(info, "OLDPWD=")) ? _dir : "/");
	}
	else
		chdir = chdir(info->argv[1]);
	if (chdir == -1)
	{
		printError(info, "can't cd to ");
		eputs(info->argv[1]), eputchar('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", _env(info, "PWD="));
		setEnv(info, "PWD", _cwd(buffer, 1024));
	}
	return (0);
}

/**
 * chdr - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int chdr(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*argArray); /* temp att_unused workaround */
	return (0);
}
