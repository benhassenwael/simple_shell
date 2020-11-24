#include "simple_shell.h"

/**
 *
 */
int __exit(char **args, gc *GC, NewCmd_t **res, char *buff)
{
	free_GC_env(GC);
	free(GC->str_coll);
	free(buff);
	if (args[1])
	{
		free_array_of_struct(res);
		exit(*args[1]);
	}
	free_array_of_struct(res);
	exit(0);
}
