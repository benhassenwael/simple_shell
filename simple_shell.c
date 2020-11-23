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
	char *str = NULL;

	gc GC;
	GC.str_coll = malloc(sizeof(gc) * 1024);
	GC.length = 0;
	NewCmd_t **result = NULL;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		err = _getline(&buffer, &n, STDIN_FILENO);
		if (err == -1)
		{
			free(buffer);
			perror("some thing wrong with getline ");
			return (-1);
		}
		buffer = _trim(&buffer, 0);
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
	return (0);
}
