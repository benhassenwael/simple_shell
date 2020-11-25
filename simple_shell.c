#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * init_gc - intialize the garbage collector
 * @GC: garbage collector
 *
 * Return: always 0
 */
int init_gc(gc *GC)
{
	int i;

	GC->str_coll = malloc(sizeof(gc) * 1024);
	GC->var_env = malloc(sizeof(gc) * 1024);
	for (i = 0; i < 1024; i++)
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
 * @argc: arguments count
 * @argv: arguments vector
 * @env: environment variables
 *
 * Return: always 0
 */
int main(__attribute__((unused))int argc, char *argv[], char **env)
{
	char *buffer = NULL;
	size_t n;
	ssize_t err;

	gc GC;
	NewCmd_t **result = NULL;
	int notatty;

	signal(SIGINT, SIG_IGN);
	init_gc(&GC);
	notatty = isatty(STDIN_FILENO);
	do {
		print_str("$ ");
		err = _getline(&buffer, &n, STDIN_FILENO);
		if (err != -1)
		{
			buffer = _trim(&buffer, 0);
			result = search_for_command(buffer);
			if (result)
			{
				exec_cmd(argv[0], result, env, &GC, buffer);
			}
		}
		free_array_of_struct(result);
	} while (notatty);
	__exit(NULL, &GC, result, buffer);
	return (0);
}
