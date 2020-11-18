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

/**
 * struct clean_command - holds a command elements
 * @command: a given command
 * @args: array of command arguments
 * @next_oper: the logical operator after the command if it exists
 */
typedef struct clean_command
{
	char *command;
	char *args[];
	char *next_oper;
} cmd_t;

#endif /* SIMPLE_SHELL_H */
