#include "simple_shell.h"
#include <stdlib.h>

/**
 * _insertTo_Env_GC - insert env variable to GC
 * @GC: gc
 * @vod: vod
 *
 * Return: 0 or -1
 */
int _insertTo_Env_GC(gc *GC, void *vod)
{

	void **p;
	int *len;

	if (!GC || !vod)
		return (-1);
	len = &(GC->env_legth);
	p = GC->var_env;
	p[*len] = vod;
	*len = *len + 1;
	p[*len] = NULL;
	return (0);
}

/**
* _insertTo_GC - when declaring a string in the heap this function take a
* pointer to that str (the string must be initialized ) and insert it to
* the struct (which is defined in the main) exactli in the array of string
* (null terminated) at last position and update the length (+1) so that can
* clear every thing at once
* @GC: pointer to the struct already initialized
* @str: string to be added
*
* Return: 0
*/

int _insertTo_GC(gc *GC, void *str)
{
	void **p;
	int *len = &(GC->length);

	if (!GC || !str)
		return (-1);
	p = GC->str_coll;
	p[*len] = str;
	*len = *len + 1;
	p[*len] = NULL;
	return (0);
}

/**
 * free_Name_from_GC - free from GC
 * @GC: gc
 * @Name: name
 *
 * Return: 0 or -1
 */
int free_Name_from_GC(gc *GC, char *Name)
{
	void **p = NULL;
	int i = 0, found = 0, *length, j;
	char **str = NULL;

	if (!Name || !GC)
		return (-1);
	p = GC->var_env;
	str = (char **)p;
	length = &(GC->env_legth);
	while (str[i])
	{
		found = checkName(str[i], Name, 0);
		if (found)
		{
			free(str[i]);
			for (j = i + 1; str[i]; j++, i++)
				str[i] = str[j];
			*length = *length - 1;
			return (0);
		}
		i++;
	}
	return (-1);
}

/**
 * free_GC_env - free gc env
 * @GC: gc
 */
void free_GC_env(gc *GC)
{
	int i = 0;
	char **str = (char **) GC->var_env;
	int *len = &GC->env_legth;

	if (GC == NULL)
		return;
	if (str != NULL)
	{
		for (i = 0; str[i] != NULL; i++)
		{
			free(str[i]);
			*len = *len - 1;
		}
	}
	free(GC->var_env);
}

/**
* free_noInUse_GC - free each element in the array of string in the struct gc
* and then free the array of string allocated
* @GC: pointet to struct gc
*
* Return: void
*/
void free_noInUse_GC(gc *GC)
{
	int i = 0;
	char **str = (char **) GC->str_coll;
	int *len = &GC->length;

	if (!GC)
		return;
	if (str)
	{
		for (i = 0; str[i] && *len > 0; i++)
		{
			free(GC->str_coll[i]);
			*len = *len - 1;
		}
	}
}
