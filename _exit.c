#include "simple_shell.h"
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
		print_str("./hsh: 1: exit: Illegal number: ");
		print_str(status);
		print_str("\n");
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
