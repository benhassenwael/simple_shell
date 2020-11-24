#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

/**
 * struct NewCmd_t - holds a command needs
 * @args: an array of pointer tostruct
 * @next_oper: char of the operator
 * @length: length of args
 * @err: 1 on error else 0
 */

typedef struct NewCmd_t
{
	char next_oper;
	char **args;
	char length;
	int err;
} NewCmd_t;

/**
 * struct G_collecttor - holds an array of pointer to be freed
 * @str_coll: an array of pointers
 * @length: length of array
 * @env_legnt: env_legth
 * @var_env: array of var
 */

typedef struct G_collecttor
{
	void **str_coll;
	void **var_env;
	int env_legth;
	int length;
} gc;

/**
 * struct exc_built - holds a func to execute
 * @name: name of a func to execute
 * @handleName: func to execute
 * this a typedef named built_func_t: for pointer to the built-in function
 */
typedef int (*builtin_func_t) (char **args, char *env[], gc *GC);
typedef struct exec_buit
{
	char *name;
	int (*handleName)(char **args, char **env, gc *GC);
} exec_buit;

/**
 * struct clean_command - holds a command elements
 * @command: a given command
 * @args: array of command arguments
 * @next_oper: the logical operator after the command if it exists
 */
typedef struct clean_command
{
	char *command;
	char *args;
	char next_oper;
} cmd_t;

void *_realloc(void *ptr, unsigned int, unsigned int);
ssize_t _getline(char **, size_t *, int);
int str_is_eq(char *, char *);
int exec_prog(char *,char **, char **);
int _help(char **, char **, gc *GC);
builtin_func_t get_builtin_func(NewCmd_t *);
char *find_prog_path(char *, char **);
NewCmd_t **search_for_command(char *);
int exec_cmd(NewCmd_t **, char **);

int _strlen(char *str);
char *_strparse(char **buffer, char *deli);
int parsedPipe(char *str, char **strpiped);
char *_trim(char **str, gc *GC);
char *_getenv(char *name, char **Dir);
char *GetAllDir(char **str);
int checkName(char *Name, char *ARG, char ch);
char *_strConcatEnv(char *str1, char *cop, int ch, gc *GC);
void parseSpecialChar(char *str, char **parsed, char *sep, char *sep2);
void free_noInUse_GC(gc *GC);
int free_Name_from_GC(gc *GC, char *Name);
void free_GC_env(gc *GC);
char *_copAlloc(char *str, gc *GC);
char *delete_comment(char **str);
char *_strparse(char **buf, char *sep);
char *extractValue(char *Name, char *STR);
int _printArrayOfStrings(char **ptr, int length);
int _insertTo_GC(gc *GC, void *str);
void *_realloc(void *ptr, unsigned int, unsigned int);
ssize_t _getline(char **, size_t *, int);
NewCmd_t *parseLine(char *line);
/*
*/
int free_array_of_struct(NewCmd_t **arr);
int str_is_eq(char *str1, char *str2);
int setttenv(char **args, char **env, gc *newGC);
int _cd(char **args, char **env, gc *newGC);
int _insertTo_Env_GC(gc *GC, void *vod);
int exec_buit_ins(NewCmd_t *cmd, char **env, gc *GC);
int _printEnv(char **args, char **env, gc *GC);
int _unset_env(char **args, char **env, gc *GC);
int _setenv(char **args, char **env, gc *GC);
int checkAndSet(char **env, char *Name, char *value, int overwrite, gc *GC);

int _Appand_command(char *str, char *fileName, gc *GC);

int _history(char **args, char **env, gc *GC);

NewCmd_t **search_for_command(char *str);











#endif /* SIMPLE_SHELL_H */
