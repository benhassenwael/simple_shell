#include "simple_shell.h"
#include <stdlib.h>



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

	char newPWD[1000];
	char oldPWD[1000];
	int i = 0, err;

	getcwd(oldPWD, 1000);

	err = chdir(str);
	if (err < 0)
	{
		printf(" error = %d\n", err);
		return (-1);
	}
	getcwd(newPWD, 1000);
	_setenv(env, "PWD", newPWD, 1, GC);
	_setenv(env, "OLDPWD", oldPWD, 1, GC);


	printf(" newPWD = %s\n", newPWD);
	printf(" oldPWD = %s\n", oldPWD);

	return (0);
}






/**
* _cd - cd builting treat changes of directories handle "~" "-"
* @cmd: pointer to struct
* @env: env var
*
* Return: 0
* Error: -1
*/
int _cd(NewCmd_t *cmd, char **env)
{
	char *home = NULL, *oldPath = NULL, *fstArg = NULL, found = 0, st = 0;
	gc GC;

	GC.str_coll = malloc(sizeof(gc) * 1024);
	GC.length = 0;
	home = _getenv("HOME", env);
	home = _strConcatEnv("/", home, 0, &GC);
	oldPath = _getenv("OLDPWD", env);

	if (!cmd || !cmd->args || !env)
		return (-1);
	fstArg = cmd->args[1];
	if (fstArg)
	{
		found = checkName("-", fstArg, 0);
		if (found)
		{
			st = change_directory(oldPath, env, &GC);
			free_Garbage_coll(&GC);
			return (st < 0 ? (-1) : (0));
		}
		else if (checkName("~", fstArg, 0))
		{
			change_directory(home, env, &GC);
			free_Garbage_coll(&GC);
			return (st < 0 ? (-1) : (0));
		}
		else
		{
			change_directory(fstArg, env, &GC);
			free_Garbage_coll(&GC);
			return (st < 0 ? (-1) : (0));
		}
	}
	else
	{
		change_directory(home, env, &GC);
		free_Garbage_coll(&GC);
		return (st < 0 ? (-1) : (0));
	}
}


