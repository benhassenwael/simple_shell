#include "simple_shell.h"
#include <stdlib.h>
/**
* free_struct - free newCmd_t struct containing an array of strings
* @st: newCmd_t
*
* Return: void
*/

void free_struct(NewCmd_t *st)
{
	int i = 0;

	if (st && st->args)
	{
		while (st->args[i])
		{
			free(st->args[i]);
			i++;
		}
		free(st->args[i]);
		free(st->args);
		free(st);
	}
}

/**
* free_array_of_struct - free array of struct nullterminated
* @arr: arr of struct
*
* Return: 0
* Error: -1
*/

int free_array_of_struct(NewCmd_t **arr)
{
	int i = 0;

	if (!arr)
		return (-1);

	while (arr[i])
	{
		free_struct(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
	return (0);
}
