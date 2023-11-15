#include "main.h"

/**
 * parse_commandl - Parse and execute command lines.
 * @sh: Shell structure.
 * @user_input: User input string.
 *
 * Return: 0 on exit, 1 to continue.
 */
int parse_commandl(myshell *sh, char *user_input)
{
	int loop;
	myseparator *s_head = NULL, *s_current;
	mycline *c_head = NULL, *c_current;

	create_nodes(&s_head, &c_head, user_input);
	s_current = s_head;
	c_current = c_head;

	for (; c_current != NULL;)
	{
		sh->user_input = c_current->line;
		sh->args = toke_commandl(sh->user_input);
		loop = find_execommand(sh);
		free(sh->args);

		if (loop == 0)
		{
			break;
		}

		next_commandl(&s_current, &c_current, sh);

		if (c_current != NULL)
		{
			c_current = c_current->next;
		}
	}

	free_separator_list(&s_head);
	free_cline_list(&c_head);

	switch (loop)
	{
		case 0:
			return (0);

		default:
			return (1);
	}
}
