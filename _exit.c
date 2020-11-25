#include "simple_shell.h"

/**
 * __exit - exit built-in func
 * @args: eguments for the func
 * @GC: garbage collector
 * @res: cammands list
 * @buff: buffer
 *
 * Return: -1 only on failure
 */
int __exit(char **args, gc *GC, NewCmd_t **res, char *buff)
{
	int i, val = 0;
	char *status;

	if (args == NULL || args[1] == NULL)
	{
		free_GC_env(GC);
		free(GC->str_coll);
		free(buff);
		free_array_of_struct(res);
		exit(0);
	}
	status = args[1];
	for (i = 0; status[i]; i++)
	{
		if (status[i] >= '0' && status[i] <= '9')
		{
			val *= 10;
			val += status[i] - '0';
		}
		else
		{
			print_str("Error: wrong parameter type\n");
			return (-1);
		}
	}
	free_GC_env(GC);
	free(GC->str_coll);
	free(buff);
	free_array_of_struct(res);
	exit(val);
}
