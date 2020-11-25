#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * init_gc - intialize the garbage collector
 * @GC: garbage collector
 *
 * Return: always 0
 */
int start_gc(gc *GC)
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
int main(__attribute__((unused))int argc,
		__attribute__((unused))char *argv[], char **env)
{
	char *buffer = NULL;
	size_t n;
	ssize_t err;

	gc GC;
	NewCmd_t **result = NULL;
	int notatty;

	signal(SIGINT, SIG_IGN);
	start_gc(&GC);
	notatty = isatty(STDIN_FILENO);
	do {
		err = _getline(&buffer, &n, STDIN_FILENO);
		if (err != -1)
		{
			buffer = _trim(&buffer, 0);
			result = search_for_command(buffer);
			if (result)
			{
				_printArrayOfStrings(result[0]->args);
				exec_cmd(result, env, &GC, buffer);
			}
		}
		free_array_of_struct(result);
	} while (notatty);
	__exit(NULL, &GC, result, buffer);
	return (0);
}
