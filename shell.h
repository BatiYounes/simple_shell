#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int _hsh(info_t *, char **);
int _find_builtin(info_t *);
void _find_cmd(info_t *);
void _fork_cmd(info_t *);

/* path.c */
int _is_cmd(info_t *, char *);
char *_dup_chars(char *, int, int);
char *_find_path(info_t *, char *, char *);

/* loophsh.c */
int loop_hsh(char **);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd_(char c, int fd);
int _putsfd_(char *str, int fd);

/* string_functions.c */
int _strlen_(char *);
int _strcmp_(char *, char *);
char *_starts_with(const char *, const char *);
char *_str_cat(char *, char *);

/* string_functions2.c */
char *_str_cpy(char *, char *);
char *_str_dup(const char *);
void _puts_(char *);
int _putchar_(char);

/* string_functions3.c */
char *_strn_cpy(char *, char *, int);
char *_strn_cat(char *, char *, int);
char *_str_chr(char *, char);

/* string_functions4.c */
char **_strtow(char *, char *);
char **_strtow2(char *, char);

/* memory_functions */
char *_mem_set(char *, char, unsigned int);
void _ffree(char **);
void *_realloc_(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int _bfree(void **);

/* more_functions.c */
int _interactive(info_t *);
int is_delim_(char, char *);
int _is_alpha(int);
int _atoi_(char *);

/* more_functions2.c */
int _erratoi_(char *);
void _print_error(info_t *, char *);
int print_d(int, int);
char *_convert_number(long int, int, int);
void _remove_comments(char *);

/* builtin_emulators.c */
int _myexit(info_t *);
int _cd(info_t *);
int _help(info_t *);

/* builtin_emulators2.c */
int _history(info_t *);
int _my_alias(info_t *);

/* getline.c module */
ssize_t _get_input(info_t *);
int _get_line(info_t *, char **, size_t *);
void _sigintHandler(int);

/* info.c module */
void _clear_info(info_t *);
void _set_info(info_t *, char **);
void _free_info(info_t *, int);

/* env.c module */
char *_get_env(info_t *, const char *);
int _my_env(info_t *);
int _myset_env(info_t *);
int _myunset_env(info_t *);
int _populate_env_list(info_t *);

/* env2.c module */
char **_get_environ(info_t *);
int _unset_env(info_t *, char *);
int _set_env(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int _write_history(info_t *info);
int _read_history(info_t *info);
int _build_history_list(info_t *info, char *buf, int linecount);
int _renumber_history_(info_t *info);

/* liststr.c module */
list_t *_add_node(list_t **, const char *, int);
list_t *add_node_end_(list_t **, const char *, int);
size_t printlist_str(const list_t *);
int del_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);

/* liststr2.c module */
size_t _list_len(const list_t *);
char **_list_to_strings(list_t *);
size_t prnt_list(const list_t *);
list_t *node_starts(list_t *, char *, char);
ssize_t getnode_index(list_t *, list_t *);

/* chain.c */
int _is_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int _replace_alias(info_t *);
int _replace_vars(info_t *);
int _replace_string(char **, char *);

#endif
