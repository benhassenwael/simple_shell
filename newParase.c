#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/cdefs.h>

#define isAlpha(X) ((*X >= 'A' && *X <= 'Z') || (*X >= 'a' && *X <= 'z'))

#define foundAND(X) (*X == '&' && *(X + 1) == '&')
#define foundOR(X) (*X == '|' && *(X + 1) == '|')

/**
* insertToLastPosion - create newptr allocate length + 1, copy all content for
* the old one insert the pointer sent to the last mostition
* @ptr: array of pointer
* @str: pointer to add to last position
* @prevLength: length of the old array
*
* Return: void
*/

void **insertToLastPosion(void **ptr, void *str, int prevLength)
{
	void **newAllocation = NULL;
	int i = 0;

	newAllocation = malloc(sizeof(char *) * (prevLength + 1));

	if (prevLength == 0)
	{
		newAllocation[prevLength] = str;
		return (newAllocation);
	}

	for (i = 0; i < prevLength; i++)
		newAllocation[i] = ptr[i];

	newAllocation[i] = str;

	free(ptr);
	return (newAllocation);
}

/**
 * create_struct - create an array of char from a string,create newCmd_t struct
 * @str: pointer to string
 * @op: operator
 *
 * Return: newCmd_t struct
 */
NewCmd_t *create_struct(char **str, char op)
{
	void **args = 0;
	char *tmp = NULL;
	int nbOfargs = 0, i = 0;
	NewCmd_t *cmd, *stop;

	if (**str == '\0' || !*str)
		return (NULL);
	cmd = malloc(sizeof(NewCmd_t));
	while (1)
	{
		tmp = _strparse(str, " ");
		if (!tmp)
			break;
		tmp = _copAlloc(tmp, 0);
		args = insertToLastPosion(args, tmp, nbOfargs);
		nbOfargs++;
	}
	args = insertToLastPosion(args, NULL, nbOfargs);

	cmd->args = (char **)args;
	cmd->next_oper = op;
	cmd->length = nbOfargs;
	cmd->err = 0;
	return (cmd);

}

/**
* insert_to_AOC - allocate the string send, create a struct, and insert it
* in the last position of an array
* @com: command
* @ar: ptr to array of struct
* @i: nbCom
* @str: point to the str
* @adv: nb of char to advance
*
* Return: 0
* Errot: -1
*/

int insert_to_AOC(char **str, char **com, void ***ar, int *i, int adv)
{
	NewCmd_t *cmd;
	char **t, op;

	op = **str;
	**str = '\0';
	*str = *str + adv;


	cmd = create_struct(com, op);
	*ar = insertToLastPosion(*ar, cmd, *i);
	*i = *i + 1;

	if (isAlpha(*str))
	{
		*com = *str;
		return (0);
	}
	else if (!*com)
	{
		return (0);
	}
	return (0);
}


/**
* search_for_command - search for command
* @str: string
*
* Return: array of pointer to struct
*/

NewCmd_t **search_for_command(char *str)
{
	char *com = str, *oldStr, op;
	NewCmd_t *cmd, **newCmd;
	int i = 0, nbCom = 0, st = 0;
	void **AOC = NULL;

	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (foundAND(str) || foundOR(str))
		{
			if (isAlpha((str + 3)))
				insert_to_AOC(&str, &com, &AOC, &nbCom, 3);
			else
			{
				return (NULL);
			}
		}
		if (*str == ';')
		{
			if (isAlpha((str + 3)))
				insert_to_AOC(&str, &com, &AOC, &nbCom, 2);
			else
				return (NULL);
		}
		str++;
	}
	insert_to_AOC(&str, &com, &AOC, &nbCom, 0);
	AOC = insertToLastPosion(AOC, NULL, nbCom);
	newCmd = (NewCmd_t **)AOC;
	return (newCmd);
}

