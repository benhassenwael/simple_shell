#include "simple_shell.h"

/**
 * exec_prog - fork and execute a program
 * @prog: full path of the program
 * @args: arguments for the program
 * @env: environment variables
 *
 * Return: the exit status of the executed program or -1 on failure
 */
int exec_prog(char *prog, char **args, char **env)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	if (child_pid == 0)
	{
		execve(prog, args, env);
		perror("Error: execve:");
		return (-1);
	}
	else
	{
		wait(&status);
		return (status);
	}
	return (0);
}
