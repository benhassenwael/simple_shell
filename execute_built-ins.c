#include "simple_shell.h"

/**
* get_builtin_func - check for the right function by checking the given and
* the write ones
* @cmd: pointer to a struct
*
* Return: function( **args, **env)
* Error: NULL
*/

builtin_func_t get_builtin_func(NewCmd_t *cmd)
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
	for (i = 0; exec[i].name && cmd; i++)
	{
		found = str_is_eq(cmd->args[0], exec[i].name);
		if (found)
		{
			return (exec[i].handleName);
		}
	}

	return (NULL);
}


