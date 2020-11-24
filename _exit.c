#include "simple_shell.h"

/**
 *
 */
int __exit(char **args, char **env, gc *g)
{
	if (args[1])
		exit(*args[1]);
	exit(0);
}
