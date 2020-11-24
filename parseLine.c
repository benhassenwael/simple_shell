
#include "simple_shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define trLen(X) (trimed[len - 1] == X)
#define foundOR(X) ((*(X) == '|' && *((X) + 1) == '|'))
#define foundAND(X) ((*(X) == '&' && *((X) + 1) == '&'))

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
	if (**arg)
	{
		printf("we enter cond;");
		while (1)
		{
			ptr = _strparse(arg, " ");
			buff[lenOfargs] = _copAlloc(ptr, GC);
			//printf(" buff[lenOfargs] = %s\n", buff[lenOfargs]);
			if (!buff[lenOfargs])
				break;
			lenOfargs++;
		}
	}
	arOfargs = malloc(sizeof(char *) * lenOfargs);

	//printf(" lenOfargs = %d\n", lenOfargs);
	arOfargs[0] = buff[0];
	i = 1;
	while (i < lenOfargs)
	{
		arOfargs[i] = buff[i];
		//printf(" arOfargs[i] = %s\n", arOfargs[i]);
		i++;
	}
	printf(" lenOfargs = %d\n", lenOfargs);
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
	printf(" **args = %d\n", *args);
	printf(" *args = %s\n", args);
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
	char *com, *args = NULL, *ptr, **result, *ar = NULL;
	int i, valAND = '&' + '&', valOR = '|' + '|';
	int curAndnext;

	cmd.args = NULL;
	cmd.next_oper = '\0';
	cmd.length = 0;
	/* we dint found an error */
	cmd.err = 0;
	if (!*line || **line == '\0')
	{
		printf("err \n" );
		return (cmd);
	}

	com = args = ptr = *line;
	printf(" **line = %c\n", **line);
	while (**line)
	{
		curAndnext = **line + *(*line + 1);
		//if (curAndnext == valAND || curAndnext == valOR)
		if (foundOR(*line) || foundAND(*line))
		{
			printf("dound \n" );
			return (create_struc(line, com, args, GC, 3));
		}
		if (**line == ';')
			return (create_struc(line, com, args, GC, 2));
		(*line)++;
	}
	printf("go out while\n" );
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

	NewCmd_t newStruct, error;
	NewCmd_t *newContainer, *old_container;
	int i = 0;

	error.args = NULL;
	error.err = 0;
	error.length = 1;
	error.next_oper = '\0';
	old_container = container;
	newContainer = malloc(sizeof(cmd_t) * (length));

	if (length == 1)
	{
		newContainer[length - 1] = NewCmd;
		//newContainer[length] = error;
		return (newContainer);
	}
	while (i < length - 1)
	{

		newContainer[i] = container[i];
		i++;
	}
	newContainer[length - 1] = NewCmd;
	//newContainer[length] = error;
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

	//free_Garbage_coll(GC);
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
	//free_Garbage_coll(&GC);
	//free_struct_cmd(result, len);
	return (result);
}

