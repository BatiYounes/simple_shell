#include "main.h"

/**
 * create_nodes - Create nodes for command lines and separators.
 * @s_head: Head of separator linked list.
 * @c_head: Head of command line linked list.
 * @user_input: User input string.
 *
 * Return: nothing.
 */
void create_nodes(myseparator **s_head, mycline **c_head, char *user_input)
{
	char *command_line;
	int j;

	user_input = rm_non_print(user_input);

	j = 0;
	while (user_input[j])
	{
		if (user_input[j] == ';')
		{
			append_separator(s_head, user_input[j]);
		}
		if (user_input[j] == '|' || user_input[j] == '&')
		{
			append_separator(s_head, user_input[j]);
			j++;
		}
		j++;
	}

	command_line = tokenize_string(user_input, ";|&");
	do {
		command_line = rest_non_print(command_line);
		append_commandl(c_head, command_line);
		command_line = tokenize_string(NULL, ";|&");
	} while (command_line != NULL);
}

/**
 * next_commandl - Get the next command line based on separators.
 * @set: Separator list.
 * @com: Command line list.
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */
void next_commandl(myseparator **set, mycline **com, myshell *sh)
{
	mycline *command_line = *com;
	myseparator *separator = *set;
	int i, s = sh->status;

	for (i = 1; i && separator != NULL;)
	{
		if (s == 0)
		{
			if (separator->symbol == '&' || separator->symbol == ';')
			{
				i = 0;
			}
			if (separator->symbol == '|')
			{
				command_line = command_line->next;
				separator = separator->next;
			}
		}
		else
		{
			if (separator->symbol == '|' || separator->symbol == ';')
			{
				i = 0;
			}
			if (separator->symbol == '&')
			{
				command_line = command_line->next;
				separator = separator->next;
			}
		}
		if (!i && separator != NULL)
		{
			separator = separator->next;
		}
	}
	*set = separator;
	*com = command_line;
}
