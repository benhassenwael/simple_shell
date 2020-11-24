#include "simple_shell.h"

/**
 *
 */
int __exit(char **args, char **env, gc *GC)
{
	
	free_GC_env(GC);
	free(GC->str_coll);
	if (args[1])
		exit(*args[1]);

	exit(0);
}
