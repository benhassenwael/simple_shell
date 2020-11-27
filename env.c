#include "simple_shell.h"

/**
* delete_env - delete one variable from the array (we put the found variable
* at the last postion and since **env is null terminated it wont bet seen for
* any other changes)
* @env: poiter to the environ array of string
* @Name: var name to delete
* @GC: garbage collector
*
* Return: 0
* Error: -1
*/
int delete_env(char **env, char *Name, gc *GC)
{
	int i, found = 0, j = 0;

	i = 0;
	while (env[i])
	{
		found = checkName(Name, env[i], 0);
		if (found)
		{
			free_Name_from_GC(GC, Name);
			for (j = i + 1; env[i]; j++, i++)
				env[i] = env[j];
			break;
		}
		i++;
	}
	return (0);
}

/**
 * _unset_env - search for Name of the var env and delete it
 * @args: array of strings
 * @env: var environment
 * @GC: gc
 *
 * Return: 0
 * Error: -1
 */
int _unset_env(char **args, char **env, gc *GC)
{
	char *Name = args[1];

	if (!args || !env || args[2] || !args[1])
		return (-1);
	delete_env(env, Name, GC);
	return (0);
}

/**
* checkAndSet - take the name and the value of the Variable u want to add
* to the
* environment variables, check if u want to overwrite it if it exist.
* @env: poiter to an array of strings
* @Name: name of the variable
* @value: value to add/apdate
* @overwrite: overwrite existing value 1 yes 0 no
* @GC: pointer to garbage collector
* Return: 0
* Error: -1
*/
int checkAndSet(char **env, char *Name, char *value, int overwrite, gc *GC)
{
	int i = 0, found = 0;

	while (env[i])
	{
		found = checkName(Name, env[i], '=');
		if (found == 2)
			return (-1);
		if (found == 1)
		{
			if (overwrite)
			{
				env[i] = _strConcatEnv(Name, value, '=', 0);
				_insertTo_Env_GC(GC, env[i]);
				return (0);
			}
		}
		i++;
	}
	env[i] = _strConcatEnv(Name, value, '=', 0);
	_insertTo_Env_GC(GC, env[i]);
	env[i + 1] = NULL;
	return (0);
}


/**
 * _getenv - loop in the env array and return the value of the env name given
 * if it is found else return NULL
 * @name: str
 * @env: pointer to array of string
 *
 * Return: pointer to the beginning of the located substring,
 *	or NULL if the substring is not found.
 */
char *_getenv(char *name, char **env)
{
	int found = 0, i = 0;

	while (env[i])
	{
		found = checkName(name, env[i], 0);
		if (found)
		{
			return (extractValue(name, env[i]));
		}
		i++;
	}
	return (NULL);
}

/**
 * _setenv - built-in func set an environment variable
 * @args: arguments
 * @env: env varaibles
 * @newGC: garbage collector
 *
 * Return: 0
 */
int _setenv(char **args, char **env, gc *newGC)
{
	char *Name = args[1];
	char *Value = args[2];

	if (Name && Value && args[0])
	{
		checkAndSet(env, Name, Value, 1, newGC);
	}
	free_noInUse_GC(newGC);
	return (0);
}
