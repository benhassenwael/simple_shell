#include "simple_shell.h"
#include <stdio.h>


/**
* check_Built_in_Name - check for the right function by checking the given and
* the write ones
* @cmd: pointer to a struct
*
* Return: function( **args, **env)
* Error: NULL
*/

int (*check_Built_in_Name(NewCmd_t *cmd))(NewCmd_t *cmd, char **env, gc *GC)
{
	int i = 0, found = 0;

	exc_built exec[] = {
		{"cd", _cd},
		{"setenv", setttenv},
		{NULL, NULL}
	};

	/* only enter when cmd->command is not null */
	for (i = 0; exec[i].name && cmd->args[0]; i++)
	{
		found = checkName(cmd->args[0], exec[i].name, 0);
		if (found == 1)
			return (exec[i].handleName);
	}

	return (NULL);
}

/**
* exec_buit_ins - execute the right function to do the job after getting it
* @cmd: pointer to a struct
* @env: pointer to env variables
*
* Return: 0
* Error: -1
*/

int exec_buit_ins(NewCmd_t *cmd, char **env, gc *GC)
{
	/* we will send the adressof the args cause we we gonna do _parse later */
	int (*ret_function)(NewCmd_t *cmd, char **env, gc *GC);

	ret_function = check_Built_in_Name(cmd);
	if (ret_function)
		ret_function(cmd, env, GC);
	else
	{
		perror(" built-in not found ");
		return (-1);
	}
	return (0);
}

