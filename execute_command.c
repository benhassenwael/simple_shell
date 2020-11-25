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
 * @name: program name used for error print
 * @cmd_list: list of commands
 * @env: the environment variables
 * @GC: garbage collector
 * @buff: buffer
 *
 * Return: always 0
 */
void exec_cmd(char *name, NewCmd_t **cmd_list, char **env, gc *GC, char *buff)
{
	int err, did_succ = 1;
	builtin_func_t builtin_func = NULL;
	char *prog_path = NULL, prev_op = '&';
	NewCmd_t *cmd_arr;

while (*cmd_list)
{
	cmd_arr = *cmd_list;
	if (should_execute(did_succ, prev_op))
	{
		if (str_is_eq(cmd_arr->args[0], "exit"))
		{
			__exit(cmd_arr->args, GC, cmd_list, buff);
			return;
		}
		builtin_func = get_builtin_func(cmd_arr);
		if (builtin_func != NULL)
		{
			err = builtin_func(cmd_arr->args, env, GC);
			if (err)
				did_succ = 0;
		}
		else
		{
			prog_path = find_prog_path(cmd_arr->args[0], env);
			if (prog_path != NULL)
			{
			did_succ = !exec_prog(prog_path, cmd_arr->args, env);
			if (!str_is_eq(cmd_arr->args[0], prog_path))
			free(prog_path);
			}
			else
			{
				print_str(name);
				print_str(": No such file or directory\n");
				did_succ = 0;
			}
		}
	}
	prev_op = cmd_arr->next_oper;
	cmd_list++;
}
}
