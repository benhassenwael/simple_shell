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
	int fd, i = 0, ref = 0;
	char *str = NULL;

	gc GC;
	GC.str_coll = malloc(sizeof(gc) * 1024);
	GC.var_env = malloc(sizeof(gc) * 1024);
	GC.env_legth = 0;
	GC.length = 0;
	NewCmd_t **result = NULL;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		printf("%s$ ", _getenv("PWD", env));
		err = _getline(&buffer, &n, STDIN_FILENO);
		create_Ref_to_Command(buffer, ref, "./his", &GC);
		ref ++;
		buffer = _trim(&buffer, 0);
		if (!buffer)
			continue;
		if (err == -1)
		{
			free(buffer);
			free_GC_env(&GC);
			free(GC.str_coll);
			perror("some thing wrong with getline ");
			return (-1);
		}
		printf(" --->%s<----\n",buffer);
		result = search_for_command(buffer);
		if (!result)
		{
			perror("pleas check spelling in ur command");
		}
		else
		{
			i = 0;
			while (result[i])
			{
				_printArrayOfStrings(result[i]->args, 0);
				exec_buit_ins(result[i], env, &GC);
				i++;
			}
		}
		free_array_of_struct(result);
	}
	free_GC_env(&GC);
	free(GC.str_coll);
	return (0);
}
