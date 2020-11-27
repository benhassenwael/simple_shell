#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/**
* change_directory - change current directory and update the envi variable, and
* handle cd -
* @str: path
* @env: pointer to the array of str
* @GC: pointer to gc
*
* Return: 0
* Error: -1
*/

int change_directory(char *str, char **env, gc *GC)
{

	char newPWD[1000], *copy = NULL;
	char oldPWD[1000];
	int err;

	getcwd(oldPWD, 1000);
	copy = _copAlloc(str, 0);
	err = chdir(str);
	if (err < 0)
	{
		write(STDERR_FILENO, "./hsh: 1: cd: can't cd to ", 26);
		write(STDERR_FILENO, copy, _strlen(copy));
		write(STDERR_FILENO, "\n", 1);
		free(copy);
		return (-1);
	}
	getcwd(newPWD, 1000);
	checkAndSet(env, "PWD", newPWD, 1, GC);
	checkAndSet(env, "OLDPWD", oldPWD, 1, GC);
	return (0);
}






/**
* _cd - cd builting treat changes of directories handle "~" "-"
* @args: array of strings null terminated
* @env: env var
* @GC: gc
*
* Return: 0
* Error: -1
*/
int _cd(char **args, char **env, gc *GC)
{
	char *home, *oldPath, *fstArg = NULL, found = 0, st = 0, *PWD = NULL;

	if (!args[0] || !args || !env)
		return (-1);
	home = _getenv("HOME", env);
	PWD = _getenv("PWD", env);
	home = _strConcatEnv("/", home, 0, GC);
	oldPath = _getenv("OLDPWD", env);
	fstArg = args[1];
	if (fstArg)
	{
		found = checkName("-", fstArg, 0);
		if (found)
		{
			if (args[2])
			{
				st = change_directory(args[2], env, GC);
				return (st < 0 ? (-1) : (0));
			}
			st = change_directory(oldPath, env, GC);
			free_noInUse_GC(GC);
			return (st < 0 ? (-1) : (0));
		}
		else
		{
			change_directory(fstArg, env, GC);
			free_noInUse_GC(GC);
			return (st < 0 ? (-1) : (0));
		}
	}
	else
	{
		if (!home)
			home = PWD;
		change_directory(home, env, GC);
		free_noInUse_GC(GC);
		return (st < 0 ? (-1) : (0));
	}
}


