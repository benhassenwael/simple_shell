#include "simple_shell.h"

/**
 * _getenv - get an environment variable
 * @name: name of the variable
 * @env: list of the environment variables
 *
 * Return: pointer to the value of the wanted variable or
 * NULL if not found
 */
char *_getenv(char *name, char **env)
{
	int i, j;
	char *var;

	for (i = 0; env[i] != NULL; i++)
	{
		var = env[i];
		for (j = 0; name[j] && var[j] && var[j] == name[j]; j++)
			;
		if (name[j] == '\0' && var[j] == '=')
			return (var + (j + 1));
	}
	return (NULL);
}
