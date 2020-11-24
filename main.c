

#include "simple_shell.h"
#include <stdlib.h>




/**
* main - 
* @argc: nb of arguments
* @argv: arguments
*
* Return: 0
* Error: 1
int main(int argc, char *argv[], char **env)
{

	NewCmd_t *cmd;
	char *ptr = malloc(100);

	ptr ="cd";
	cmd = malloc(sizeof(NewCmd_t));

	cmd->args = malloc(sizeof(char *) * 100);
	cmd->args[0] = ptr;
	cmd->next_oper = 0;
	cmd->err = 0;
	cmd->length = 0;
	exec_buit_ins(cmd, env);
	//free(ptr);
	free(cmd->args);
	free(cmd);
	return (0);
}
*/
