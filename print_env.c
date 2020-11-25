#include "simple_shell.h"

/**
 * _printEnv - print all environment variables
 * @args: array of strings
 * @env: environment variables
 * @GC: gc
 *
 * Return: 0
 * Error: -1
 */

int _printEnv(char **args, char **env, __attribute__((unused))gc * GC)
{
	int i = 0;

	if (!args || !env)
		return (-1);
	while (env[i])
	{
		print_str(env[i]);
		print_str("\n");
		i++;
	}
	return (0);
}
