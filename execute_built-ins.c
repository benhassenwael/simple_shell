#include "simple_shell.h"
#include <stdio.h>

/**
* _help - print some message to describe buitin function
* @args: pointer to a string
* @env: pointer to array of string
*
* Return: 0
* Error: -1
*/
int _help(char **args, char **env)
{
	int i = 0;

	printf(" im the _help function ARGS passed are :%s they are not trimed \n", *args);
	printf("we need **args as params so tha we can to some job like _parse\n");
	return (0);
}





/**
* check_Built_in_Name - check for the right function by checking the given and
* the write ones
* @cmd: pointer to a struct
*
* Return: function( **args, **env)
* Error: NULL
*/

int (*check_Built_in_Name(cmd_t *cmd))(char **args, char **env)
{
	int i = 0, found = 0;

	exc_built exec[] = {
		{"cd", _cd},
		{"help", _help},
		{NULL, NULL}
	};


	/* only enter when cmd->command is not null */
	for (i = 0; exec[i].name && cmd->command; i++)
	{
		found = checkName(cmd->command, exec[i].name, 0);
		if (found == 1)
			return (exec[i].handleName);
		else
			return (NULL);
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

int exec_buit_ins(cmd_t *cmd, char **env)
{
	/* we will send the adressof the args cause we we gonna do _parse later */
	int (*ret_function)(char **args, char **env);

	ret_function = check_Built_in_Name(cmd);
	if (ret_function)
		ret_function(&cmd->args, env);
	else
	{
		perror(" built-in not found ");
		return (-1);
	}
	return (0);
}

/**
* main - exec
* @argc: nb of arguments
* @argv: arguments
*
* Return: 0
* Error: 1
*/
int main(int argc, char *argv[], char *env[])
{
	cmd_t cmd;

	cmd.command = "elp";
	cmd.args = "              sa la                   ";
	cmd.next_oper = '&';
	exec_buit_ins(&cmd, env);
	return (0);
}
