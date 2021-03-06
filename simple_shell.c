#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * init_gc - intialize the garbage collector
 * @GC: garbage collector
 *
 * Return: always 0
 */
int init_gc(gc *GC)
{
	int i;

	GC->str_coll = malloc(sizeof(gc) * 200);
	if (!(GC->str_coll))
		exit(-1);
	GC->var_env = malloc(sizeof(gc) * 200);
	if (!(GC->var_env))
		exit(-1);
	for (i = 0; i < 200; i++)
	{
		GC->str_coll[i] = NULL;
		GC->var_env[i] = 0;
	}
	GC->env_legth = 0;
	GC->length = 0;
	return (0);
}

/**
 * main - main function
 * @argv: arguments vector
 * @argc: arguments count
 * @env: environment variables
 *
 * Return: always 0
 */
int main(__attribute__((unused))int argc, char *argv[], char **env)
{
	char *buffer = NULL;
	int st = 0;

	gc GC;
	NewCmd_t **result = NULL;

	signal(SIGINT, signal_to_handel);
	init_gc(&GC);
	do {
		if (isatty(STDIN_FILENO))
			print_str("$ ");
		buffer = _getline(&GC, &st);
		if (buffer[0] == '\0' || buffer[0] == '#')
			continue;
		buffer = delete_comment(&buffer);
		if (buffer)
		{
			buffer = _trim(&buffer, &GC);
			result = search_for_command(buffer);
			if (result)
				exec_cmd(argv[0], result, env, &GC, buffer, &st);
		}
		free_array_of_struct(result);
		free(buffer);
	} while (1);
	return (0);
}
