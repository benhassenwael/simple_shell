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

typedef struct NewCmd_t
{
	char next_oper;
	char **args;
	char length;
} NewCmd_t;

typedef struct G_collecttor
{
	char **str_coll;
	int length;
} gc;

typedef struct exc_built
{
	char *name;
	int (*handleName)(char **args, char *env[]);

} exc_built;


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

char *_strparse(char **buffer, char *deli);
int parsedPipe(char *str, char **strpiped);
char *_trim(char **str, gc *GC);
char *_getenv(char *name, char **Dir);
char *GetAllDir(char **str);
int checkName(char *Name, char *ARG, char ch);
char *_strConcatEnv(char *str1, char *cop, int ch, gc *GC);
void parseSpecialChar(char *str, char **parsed, char *sep, char *sep2);
int _insertTo_GC(gc *GC, char *str);
int _setenv(char **env, char *Name, char *value, int overwrite, gc *GC);
int _delete_env(char **env, char *Name);
void free_Garbage_coll(gc *GC);
char *_copAlloc(char *str, gc *GC);
char *delete_comment(char **str);
char *_strparse(char **buf, char *sep);
int _cd(char **args, char **env);
char *extractValue(char *Name, char *STR);
int _printArrayOfStrings(char **ptr, int length);
int _insertTo_GC(gc *GC, char *str);
void *_realloc(void *ptr, unsigned int, unsigned int);
ssize_t _getline(char **, size_t *, int);
NewCmd_t *parseLine(char *line);















#endif /* SIMPLE_SHELL_H */
