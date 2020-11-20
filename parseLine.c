
#include "simple_shell.h"
#include <readline/chardefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define trLen(X) (trimed[len - 1] == X)
#define foundOR(X) ((*(X) == '|' && *((X) + 1) == '|'))
#define foundAND(X) ((*(X) == '&' && *((X) + 1) == '&'))

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
				return (ptr); /* end loop by sending char* */
			}
		}
		(*buf)++;
	}
	/* in the las word we wont found any sep we return what we have*/
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

	if (!*str)
		return (ptr);
	ptr = _strparse(str, "#");
	return (ptr);
}

/**
* free_struct_cmd - free the array of pointers to structs
* @result: array of pointers to struct
* @len: len of the array
* Return: void
*/

void free_struct_cmd(NewCmd_t *result, int len)
{

	int i = 0;

	while (i < len)
	{
		/*
		 * we only free the array of strings because GC will handle
		 * strings
		 */
		free(result[i].args);
		i++;
	}
	/* free the array of pointer to struct*/
	free(result);
}

/**
* Clean_string - create a single space before and after the operator "&&",
* "||",";" so it can feet our logic later on
* @str: str
*
* Return: pointer
*/

char *Clean_string(char *str)
{
	char trimed[1024], op, *tr;
	int i = 0;

	while (*str)
	{
		if (foundOR(str) || foundAND(str) || *str == ';')
		{
			op = *str;
			if (*(str - 1) != ' ')
			{
				trimed[i++] = ' ';
			}
			if (op == ';')
			{
				str++;
				trimed[i++] = op;
			}
			else
			{
				str = str + 2;
				trimed[i++] = op;
				trimed[i++] = op;
			}
			if (*(str) != ' ')
			{
				trimed[i++] = ' ';
			}
		}
		trimed[i++] = *str;
		str++;
	}
	trimed[i] = '\0';
	tr = trimed;
	return (tr);
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
	char trimed[500], *vide, op, *tmp;
	int i = 0, len = 0;

	while (**str)
	{
		if (**str == ' ')
		{
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
		tmp++;
	}
	trimed[i] = '\0';
	if (*trimed == '\0')
		return (NULL);
	len = strlen(trimed);
	if (trimed[len - 1] == ' ' || trLen('\t') || trLen('\n'))
		trimed[len - 1] = '\0';
	len = strlen(trimed);
	if (trimed[len - 1] == ' ' || trLen('\t') || trLen('\n'))
		trimed[len - 1] = '\0';
	if (trimed[0] == ' ' || trimed[0] == '\t' || trimed[0] == '\n')
	{
		i = 0;
		while (trimed[i])
		{
			trimed[i] = trimed[i + 1];
			i++;
		}
	}
	tmp = Clean_string(trimed);
	return (_copAlloc(tmp, GC));
}



/**
* appand_To_NewCmd_t - filling an empty array of strings, to know the lenOfargs
* loop throu it in each iteration split the full string of args got from the
* parent and save each token got from  _strparse by the delimitaion " ", then
* copie each elemnt of this array to new array which we know exactly how much
* we could allocate in memory
* @cmd: pointer to a struct
* @command string to index 0 and then allocate all strings now we just coppy
* them into an allocated array of string that have the wright size of token
* found on each command
* @arg: string of all args
* @command: name the the command
* @GC: pointer to gc
*
* Return: allocated array of string
*/

char **appand_To_NewCmd_t(NewCmd_t *cmd, char **arg, char *command, gc *GC)
{
	int lenOfargs = 1, i = 1;
	char *ptr, *buff[1024];
	char **arOfargs = NULL;

	buff[0] = _copAlloc(command, GC);
	while (1)
	{
		ptr = _strparse(arg, " ");
		buff[lenOfargs] = _copAlloc(ptr, GC);
		if (!buff[lenOfargs])
			break;
		lenOfargs++;
	}
	arOfargs = malloc(sizeof(char *) * lenOfargs);

	arOfargs[0] = buff[0];
	i = 1;
	while (i < lenOfargs)
	{
		arOfargs[i] = buff[i];
		i++;
	}
	cmd->length = lenOfargs;
	return (arOfargs);
}

/**
* create_struc - spliting a string intp command, args and operator and then
* sendsending them to other function to create an array of string
* @line: full line
* @com: command
* @args: args
* @GC: garbage collector
* @adv: nb of char to advance the pointer so that it point to the next word we
* hadling && ad || it would be 3 chars and if it ";" then it woul be 2
*
* Return: new struct
*/

NewCmd_t create_struc(char **line, char *com, char *args, gc *GC, int adv)
{
	NewCmd_t cmd, err;
	char **result = NULL;

	err.args = NULL;
	err.length = 0;
	err.length = 0;
	err.err = 1;

	/*
	 * **line is alwas in advace of com and ptr unless if there is no name
	 * of the command (nothing in between 2 operators )
	 */
	cmd.next_oper = **line;
	**line = '\0';
	*line = *line + adv;
	if (**line == '|' || **line == '&' || **line == ';')
		return (err);
	while (*args != ' ' && *args)
		args++;
	*args = '\0';
	args++;
	result = appand_To_NewCmd_t(&cmd, &args, com, GC);
	cmd.args = result;
	cmd.err = 0;

	return (cmd);
}

/**
* seach_for_operator - create struct containing all argumets found (command
* name included) in an array of string  + the right operator char
* @line: pointer to a string
* @GC: garbage collector
*
* Return: newStruct
*/

NewCmd_t seach_for_operator(char **line, gc *GC)
{
	NewCmd_t cmd;
	char *com, *args, *ptr, **result, *ar = NULL;
	int i, valAND = '&' + '&', valOR = '|' + '|';
	int curAndnext;

	cmd.args = NULL;
	cmd.next_oper = '\0';
	cmd.length = 0;
	/* we dint found an error */
	cmd.err = 0;
	if (!line || **line == '\0')
		return (cmd);

	com = args = ptr = *line;
	while (**line)
	{
		curAndnext = **line + *(*line + 1);
		if (foundOR(*line) || foundAND(*line))
		{
			//if (curAndnext == valAND || curAndnext == valOR)
			return (create_struc(line, com, args, GC, 3));
		}
		if (**line == ';')
			return (create_struc(line, com, args, GC, 2));
		(*line)++;
	}
	return (create_struc(line, com, args, GC, 0));
}

/**
* _allocateNewCmd_t - create a newContainer with the size = length, copie the
* oldcontainer send into the new One, free the old one, return pointer to the
* new one
* @container: old array of string
* @NewCmd: new struct to add
* @length: new Length to allocate
* Return: pointer to newContainer
*/

NewCmd_t *_allocateNewCmd_t(NewCmd_t *container, NewCmd_t NewCmd, int length)
{

	NewCmd_t newStruct;
	NewCmd_t *newContainer, *old_container;
	int i = 0;

	old_container = container;
	newContainer = malloc(sizeof(cmd_t) * (length));

	if (length == 1)
	{
		newContainer[length - 1] = NewCmd;
		return (newContainer);
	}
	while (i < length - 1)
	{

		newContainer[i] = container[i];
		i++;
	}
	newContainer[length - 1] = NewCmd;
	old_container = container;
	free(old_container);

	return (newContainer);

}
/**
* handle_exit_error - free and element in the result element, allocate space
* for 1 strcut sets this struct to an empty struct (error)
* @result: array of struct
* @GC: garbage collector
*
* Return: void
*/

void handle_exit_error(NewCmd_t *result, gc *GC)
{
	NewCmd_t error;

	error.err = 1;
	error.length = 0;
	error.args = NULL;
	error.next_oper = '\0';

	free_Garbage_coll(GC);
	result = malloc(sizeof(NewCmd_t));
	result[0] = error;
	free(result);
	printf("***** some thing is wrong pls check spelling ******\n");

}
/**
* parseLine - trim the line given fillling an array of NewCmd and return it
* @line: char *
*
* Return: array of pointer to cmd_t
*/

NewCmd_t *parseLine(char *line)
{
	gc GC;
	NewCmd_t *result;
	NewCmd_t tmp, error;
	char *ptr;
	int i = 0, len = 0, j = 0;

	GC.str_coll = malloc(sizeof(char *) * 500);
	GC.length = 0;
	ptr = _trim(&line, &GC);
	ptr = delete_comment(&ptr);
	if (!ptr || *ptr == '&' || *ptr == '|' || *ptr == ';')
	{
		handle_exit_error(result, &GC);
		return (result);
	}
	len = 0;
	while (1)
	{
		tmp = seach_for_operator(&ptr, &GC);
		/* handel && && && if we found we retrun one empty struct */
		if (tmp.err == 1)
		{
			handle_exit_error(result, &GC);
			return (result);
		}
		if (!tmp.args)
			break;
		/*
		 * if we have an array of char in the struct we save all the
		 * struct into result
		 */
		result = _allocateNewCmd_t(result, tmp, len + 1);
		len++;
	}
	i = 0;
	while (i < len)
	{
		_printArrayOfStrings(result[i].args, result[i].length);
		i++;
	}
	free_Garbage_coll(&GC);
	free_struct_cmd(result, len);
	return (result);
}

