#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * __exit - exit built-in func
 * @args: eguments for the func
 * @GC: garbage collector
 * @res: cammands list
 * @buff: buffer
 * @st: pointer to status
 *
 * Return: -1 only on failure
 */
int __exit(char **args, gc *GC, NewCmd_t **res, char *buff, int *st)
{
	int val = 0;
	char *status;


	if (args == NULL || args[1] == NULL)
	{
		free_GC_env(GC);
		free(GC->str_coll);
		free(buff);
		free_array_of_struct(res);
		exit(WEXITSTATUS(*st));
	}
	status = args[1];
	val = _isInteger(status);
	if (!val)
	{
		perror("./hsh: 1: exit: Illegal number: ");
		perror(status);
		perror("\n");
		exit(2);
	}
	else
	{
		free_GC_env(GC);
		free(GC->str_coll);
		free(buff);
		free_array_of_struct(res);
		exit(val);
	}
}
