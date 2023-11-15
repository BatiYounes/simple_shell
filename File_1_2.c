#include "main.h"

/**
 * execute_command - Execute a command.
 * @sh: Shell structure.
 *
 * Return: 1 on success.
 */

int execute_command(myshell *sh)
{
	int state, executable;
	pid_t _pid, _mypid;
	char *cmd_directory;

	UNUSED(_mypid);

	executable = is_exe(sh);
	switch (executable)
	{
		case 0:
			cmd_directory = find_command(sh->args[0], sh->_env);
			if (command_error(cmd_directory, sh) == 1)
				return (1);
			break;
		case -1:
			return (1);
	}
	_pid = fork();
	switch (_pid)
	{
		case 0:
			if (executable == 0)
				cmd_directory = find_command(sh->args[0], sh->_env);
			else
				cmd_directory = sh->args[0];
			execve(cmd_directory + executable, sh->args, sh->_env);
			break;
		case -1:
			perror(sh->av[0]);
			return (1);
		default:
			do {
				_mypid = waitpid(_pid, &state, WUNTRACED);
			} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	sh->status = state / 256;
	return (1);
}
