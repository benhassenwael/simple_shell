#include "simple_shell.h"
#include <stdlib.h>
int _insertTo_GC(gc *GC, void *vod)
{

	void **p;
	int *len = &(GC->length), i = 0;

	if (!GC || !vod)
		return (-1);
	p = GC->str_coll;
	/* insert new string in last position*/
	p[*len] = vod;
	/* increment the length*/
	*len = *len + 1;
	/* NULL terminated array*/
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

int _insertTo_GC(gc *GC, char *str)
{

	char **p;
	int *len = &(GC->length), i = 0;
	char *ptr = NULL, *tmp = NULL;

	if (!GC || !str || *str == '\0')
		return (-1);
	p = GC->str_coll;
	p[*len] = str;
	*len = *len + 1;
	p[*len] = NULL;
	return (0);
}
*/
/* insert new string in last position*/
/* increment the length*/
/* NULL terminated array*/

/**
* free_Garbage_coll - free each element in the array of string in the struct gc
* and then free the array of string allocated
* @GC: pointet to struct gc
*
* Return: void
*/

void free_Garbage_coll(gc *GC)
{
	int i = 0;

	if (!GC)
		return;

	/* free each string existing*/

	for (i = 0; i < GC->length; i++)
	{
		free(GC->str_coll[i]);
	}
	free(GC->str_coll);
	printf("-------ok-------------\n");
	/*
	*/
	/* free NULL (defaul initialisation)*/
}
