#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *
 */
int main(int argc, char *argv[], char **env)
{
	char *buffer = NULL;
	size_t n;
	ssize_t err;
	int fd, i = 0;
	char *str = "&& help cd";

	gc GC;
	GC.str_coll = malloc(sizeof(gc) * 1024);
	GC.var_env = malloc(sizeof(gc) * 1024);
	GC.env_legth = 0;
	GC.length = 0;
	NewCmd_t **result = NULL;
	int notatty;

	signal(SIGINT, SIG_IGN);
	notatty = isatty(STDIN_FILENO);
	do {
		err = _getline(&buffer, &n, STDIN_FILENO);
		if (err != -1)
		{
			buffer = _trim(&buffer, 0);
			printf(" --->%s<----\n",buffer);
			result = search_for_command(buffer);
			if (result)
			{
				_printArrayOfStrings(result[i]->args, 0);
				exec_cmd(result, env, &GC, buffer);
			}
		}
		free_array_of_struct(result);
		//free(buffer);
	} while (notatty);
	return (0);
}
