#include "simple_shell.h"
#include <stdlib.h>
/*
*/
int _insertTo_Env_GC(gc *GC, void *vod)
{

	void **p;
	int *len = &(GC->env_legth), i = 0;

	if (!GC || !vod)
		return (-1);
	p = GC->var_env;
	p[*len] = vod;
	printf(" we insert ENV = %s\n",(char *) vod);
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
	int *len = &(GC->length), i = 0;

	if (!GC || !str)
		return (-1);
	p = GC->str_coll;
	p[*len] = str;
	printf(" we insert to no use = %s\n",(char *) str);
	*len = *len + 1;
	p[*len] = NULL;
	return (0);
}
/* insert new string in last position*/
/* increment the length*/
/* NULL terminated array*/

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
		printf(" found = %d\n", found);
		if (found)
		{
			printf("(%s) frm GC, ", str[i]);
			free(str[i]);
			printf("old length  = %d\n", *length);
			for (j = i + 1; str[i]; j++, i++)
				str[i] = str[j];
			*length = *length - 1;
			printf(" p[*length] = %s\n", str[*length]);
			printf(" *length = %d\n", *length);
			return (0);
		}
		i++;
	}
	return (-1);
}

void free_GC_env(gc *GC)
{
	int i = 0;
	char **str = (char **) GC->var_env;
	int *len = &GC->env_legth;
	if (!GC)
		return;

	/* free each string existing*/
	

	printf("------- free env -------------\n");
	for (i = 0; str[i]; i++)
	{
		printf("Env ( %s ) freed\n", str[i]);
		free(str[i]);
		*len = *len - 1;
	}
	free(GC->var_env);
	printf("-------Env ok-------------\n");


}
/**
* free_Garbage_coll - free each element in the array of string in the struct gc
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

	/* free each string existing*/

	printf("----------- free local garbage-------------\n");
	for (i = 0; str[i]; i++)
	{
		printf("no use %s freed\n", str[i]);
		free(GC->str_coll[i]);
		*len = *len - 1;
	}
	free(str[i]);
	printf(" *len = %d\n", *len);
	printf("------------ok-------------\n");
	/*
	*/
	/* free NULL (defaul initialisation)*/
}
