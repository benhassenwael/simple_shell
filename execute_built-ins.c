#include "simple_shell.h"
#include <stdio.h>

/**
* get_builtin_func - check for the right function by checking the given and
* the write ones
* @cmd: pointer to a struct
*
* Return: function( **args, **env)
* Error: NULL
*/

builtin_func_t check_Built_in_Name(char **args)
{
	int i = 0, found = 0;

	exec_buit exec[] = {
		{"cd", _cd},
		{"setenv", _setenv},
		{"help", _help},
		{"env", _printEnv},
		{"unsetenv", _unset_env},
		{"history", _history},
		{NULL, NULL}
	};

	/* only enter when cmd->command is not null */
	for (i = 0; exec[i].name && args[0]; i++)
	{
		found = str_is_eq(args[0], exec[i].name);
		if (found)
			return (exec[i].handleName);
	}

	return (NULL);
}
int exec_buit_ins(NewCmd_t *cmd, char **env, gc *GC)
{
	/* we will send the adressof the args cause we we gonna do _parse later */
	int (*ret_function)(char **args, char **env, gc *GC);

	ret_function = check_Built_in_Name(cmd->args);
	if (ret_function)
		ret_function(cmd->args, env, GC);
	else
	{
		perror(" built-in not found ");
		return (-1);
	}
	return (0);
}
