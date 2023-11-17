#include "shell.h"

/**
 * historyLs - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int historyLs(info_t *info)
{
	prntlist(info->history);
	return (0);
}

/**
 * unsetAlias - sets alias to string
 * @info: parameter struct
 * @_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *info, char *_str)
{
	char *pr, s;
	int rtn;

	pr = strChr(_str, '=');
	if (!pr)
		return (1);
	s = *pr;
	*pr = 0;
	rtn = del_node(&(info->alias),
		get_node(info->alias, startNode(info->alias, _str, -1)));
	*pr = s;
	return (rtn);
}

/**
 * setAlias - sets alias to string
 * @info: parameter struct
 * @_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *_str)
{
	char *f;

	f = strChr(_str, '=');
	if (!f)
		return (1);
	if (!*++f)
		return (unsetAlias(info, _str));

	unsetAlias(info, _str);
	return (add_node(&(info->alias), _str, 0) == NULL);
}

/**
 * prntAlias - prints an alias string
 * @_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int prntAlias(list_t *_node)
{
	char *s = NULL, *i = NULL;

	if (_node)
	{
		s = strChr(_node->_str, '=');
		for (i = _node->_str; i <= s; i++)
			putchar(*i);
		putchar('\'');
		puts(s + 1);
		puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _alias(info_t *_info)
{
	int j = 0;
	char *d = NULL;
	list_t *_node = NULL;

	if (_info->argc == 1)
	{
		_node = _info->alias;
		while (_node)
		{
			prntAlias(_node);
			_node = _node->next;
		}
		return (0);
	}
	for (j = 1; _info->argv[j]; j++)
	{
		d = strChr(_info->argv[j], '=');
		if (d)
			setAlias(_info, _info->argv[j]);
		else
			prntAlias(startNode(_info->alias, _info->argv[j], '='));
	}

	return (0);
}
