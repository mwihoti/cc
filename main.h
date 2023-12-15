#ifndef _MAIN_H_
#define  _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/* read/write buffer */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*commands */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* convert_number */

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define  USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE "Shell history by Mwihoti"
#define HIST_MAX 4096


extern char **environ;

/**
 * struct linkedlist - singly linked list
 * @num: number field
 * @str: string
 * @next: points to the next node
 */
typedef struct linkedlist
{
	int num;
	char *str;
	struct linkedlist *next;
} list_t;
/**
 * struct passinfoarg - pseudo-arguements to pass into a function
 * @arg: generated from getline string
 * @argv: an array of strings generated from arg
 * @path: string path for the current command
 * @argc: arguement count
 * @line_count: error count
 * @err_num: error code for exit
 * @linecount_flag: counts line of input
 * @fname: program filename
 * @env: copy of environ linked list
 * @environ: custom modified copy of environ
 * @history: history mode
 * @alias: alias node
 * @env_changed: check if environ changed
 * @status: return status of last exec command
 * @cmd_buf: address of pointer to cmd_buf
 * @cmd_buf_type: CMD_type || &&
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 */
typedef struct passinfoarg
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
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 * struct builtin - contains a builtin string
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char  *type;
	int (*func)(info_t *);
} builtin_table;

/*getinfo*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*getline*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*realloc*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*loop*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*environ.c*/
int _currenv(info_t *);
char *_getenviron(info_t *, const char *);
int _currsetenv(info_t *);
int _currunsetenv(info_t *);
int populates_environ_list(info_t *);
int _setsenviron(info_t *, char *, char *);
int _unsetenviron(info_t *, char *);
char **gets_environ(info_t *);
/*memory*/
int bfree(void **);

/*Exit*/
char *_stringcpy(char *, char *, int);
char *_strconcate(char *, char *, int);
char *_strchar(char *, char);

/*list*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*lst1*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* parser */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*string*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*string2*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*mode */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* free*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*tokenizer */
char **strtow(char *, char *);
char **strtow2(char *, char);

/*vars*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* builts*/
int _dishistory(info_t *);
int build_alias(info_t *);
int _getexit(info_t *);
int _changedcd(info_t *);
int _cdc(info_t *);

/*history*/
char *get_history_files(info_t *info);
int write_history(info_t *info);
int read_history_list(info_t *info, char *buf, int line_count);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int line_count);
int read_history(info_t *info);
/*error*/
int _erroratoi(char *);
void prints_error(info_t *, char *);
int prints_d(int, int);
char *convertsnumber(long int, int, int);
void removes_comments(char *);


#endif



