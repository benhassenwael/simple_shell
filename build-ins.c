

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* _strparse - take a long string and split it into multiple strings using the
* delimitaion string (any char of the sep str) if found char if we found
* @buf: long string
* @sep: delimitaion string
* Return: first token found (string before sep)
*/

char *_strparse(char **buf, char *sep)
{
	int i = 0, j = 0;
	char *ptr;

	//_trim(buf);
	if (!*buf || **buf == '\0')
	{
		*buf = NULL;
		return (NULL);
	}
	if (!sep || *sep == '\0')
		return (*buf);
	ptr = *buf;

	while (**buf)
	{
		for (j = 0; sep[j]; j++)
		{
			if (**buf == sep[j])
			{
				**buf = '\0';
				(*buf)++; /* dont stay on index of ' ' */
				//_trim(buf); /* next sentense is trimmed */
				return (ptr); /* end loop by sending char* */
			}
		}
		(*buf)++;
	}
	/* in the las word wwe wont found any sep we return what we have*/
	return (ptr);
}



/**
* delete_comment - get rid of all text after '#', take only whats before
* @str: pointer to the first token
*
* Return: char*
*/

char *delete_comment(char **str)
{

	char *ptr = NULL;

	ptr = _strparse(str, "#");
	return (ptr);
}

/**
* free_struct_cmd - free the array of pointers to structs
* @result: array of pointers to struct
*
* Return: void
*/

void free_struct_cmd(cmd_t **result)
{
	int i = 0;

	while (1)
	{
		if (!result[i]->command)
			break;
		free(result[i]->args);
		free(result[i]->command);
		free(result[i]);
		i++;

	}
	/* free last struct containing { NULL NULL '\0'}*/
	free(result[i]);
	/* free the array of pointer to struct*/
	free(result);

}
/**
* _trim - get ride off all space and '\n' and '\t' from a string and allocate
* it to the heap
* @str: line
* @GC: pointet to gc
* Return: pointer
*/

char *_trim(char **str, gc *GC)
{
	char trimed[500], *vide;
	int i = 0, len = 0;

	while (**str)
	{
		if (**str == ' ')
		{
			/* maybe we want to allocate first and the add ' ' we
			 * we found *str + 1 = char */
			vide = *str + 1;
			while (*vide == ' ' | *vide == '\t')
			{
				vide++;
				(*str)++;
			}
		}
		trimed[i] = **str;
		i++;
		(*str)++;
	}
	trimed[i] = '\0';
	len = strlen(trimed);
	if (trimed[len - 1] == ' ' || trimed[len - 1] == '\t')
		trimed[len - 1] = '\0';
	if (trimed[0] == ' ' || trimed[0] == '\t')
	{
		i = 0;
		while (trimed[i])
		{
			trimed[i] = trimed[i + 1];
			i++;
		}
	}
	return (_copAlloc(trimed, GC));
}


/**
* create_struct - create struct from the first toke found in a string command ,
* args and the operator
* @line: pointer to a string
*
* Return: newStruct
*/

cmd_t *create_struct(char **line)
{
	cmd_t *cmd = malloc(sizeof(cmd_t));
	char *com, *args, *ptr;
	int i, valAND = '&' + '&', valOR = '|' + '|';
	int curAndnext;

	cmd->args = NULL;
	cmd->command = NULL;
	cmd->next_oper = '\0';
	if (!line || **line == '\0')
		return (cmd);

	com = args = ptr = *line;
	while (**line)
	{
		curAndnext = **line + *(*line + 1);
		if (curAndnext == valAND || curAndnext == valOR)
		{
			cmd->next_oper = **line;
			**line = '\0';
			*line = *line + 3;
			while (*ptr != ' ')
				ptr++;
			*ptr = '\0';
			ptr++;
			cmd->command = _copAlloc(com, 0);
			cmd->args = _copAlloc(ptr, 0);
			return (cmd);
		}
		(*line)++;
	}
	cmd->next_oper = '\0';
	cmd->command = _copAlloc(_strparse(&ptr, " "), 0);
	cmd->args = _copAlloc(ptr, 0);
	return (cmd);
}
/**
* parseLine - trim the line given fillling an array of cmd_t and return it
* @line: char *
*
* Return: array of pointer to cmd_t
*/

cmd_t **parseLine(char *line)
{

	gc GC;
	cmd_t **result = malloc(500);
	cmd_t *test;
	char *ptr;
	int i = 0, len = 0;


	GC.str_coll = malloc(sizeof(char *) * 500);
	GC.length = 0;
	ptr = _trim(&line, &GC);
	ptr = delete_comment(&ptr);
	len = 0;
	while (len < 10)
	{
		result[len] = create_struct(&ptr);

		if (!result[len]->command)
			break;
		len++;
	}

	i = 0;
	while (i < len)
	{
		printf("c= %s, a=%s, o=%c\n",result[i]->command, result[i]->args, result[i]->next_oper );

		if (!result[i]->command)
			break;
		i++;
	}
	free_struct_cmd(result);
	free_Garbage_coll(&GC);
	return (result);
}

