#include "simple_shell.h"

/**
 * should_execute - check the previous logical operator to know if the next
 * command should execute or not
 * @did_succ: holds 0 if the previous command failed
 * @prev_op: hold the previous logical operator '&', '|' or ';'
 *
 * Return: 1 or 0
 */
int should_execute(int did_succ, char prev_op)
{
	int op;

	if (prev_op == ';')
		return (1);
	op = prev_op == '&' ? 0 : 1;
	if (did_succ)
		did_succ = 1;
	else
		did_succ = 0;
	return (op ^ did_succ);
}

/**
 * exec_cmd -  manage the execution of a given list of commands
 * @cmd_arr: list of commands
 * @env: the environment variables
 *
 * Return: always 0
 */
int exec_cmd(NewCmd_t *cmd_arr, char **env)
{
	int err;
	builtin_func_t builtin_func = NULL;
	char *prog_path = NULL, prev_op = '&';
	int did_succ = 1;

while (cmd_arr->args)
{
	if (should_execute(did_succ, prev_op))
	{
		builtin_func = get_builtin_func(cmd_arr);
		if (builtin_func != NULL)
		{
			err = builtin_func(cmd_arr->args, env);
			if (err)
				did_succ = 0;
		}
		else
		{
			prog_path = find_prog_path(cmd_arr->args[0], env);
			if (prog_path != NULL)
			did_succ = !exec_prog(prog_path, cmd_arr->args, env);
			else
			{
				perror("command not found");
				did_succ = 0;
			}
		}
	}
	prev_op = cmd_arr->next_oper;
	cmd_arr++;
}
return (0);
}

void main(int c, char **v, char **env)
{
	NewCmd_t cmd, cmd1;

	cmd.args = malloc(sizeof(char *) * 3);
	cmd.args[0] = "help";
	cmd.args[1] = "cd";
	cmd.args[2] = NULL;
	cmd.next_oper = '|';
	cmd1.args = malloc(sizeof(char *) * 3);
	cmd1.args[0] = "help";
	cmd1.args[1] = "cd";
	cmd1.args[2] = NULL;
	cmd1.next_oper = '|';
	NewCmd_t cmd_list[] = {cmd, cmd1, NULL};

	exec_cmd(cmd_list, env);
}
