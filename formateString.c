#include "simple_shell.h"
#include <stdlib.h>



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
	int j = 0;
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
				(*buf)++;
				return (ptr);
			}
		}
		(*buf)++;
	}
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
* Clean_string - create a single space before and after the operator "&&",
* "||",";" so it can feet our logic later on, then allocate it
* @str: str
* @GC: gc
*
* Return: pointer
*/

char *Clean_string(char *str, __attribute__((unused))gc * GC)
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
			if (*str != ' ')
			{
				trimed[i++] = ' ';
			}
		}
		trimed[i++] = *str;
		str++;
	}
	trimed[i] = '\0';
	tr = _copAlloc(trimed, 0);
	return (tr);
}
/**
* _trim - get ride off all space and '\n' from a string
* @str: line
* @GC: pointet to gc
* Return: pointer
*/

char *_trim(char **str, __attribute__((unused))gc * GC)
{
	char trimed[500], *tmp, *oldBuff = *str;
	int i = 0, len = 0;

	for (i = 0; (*str)[i]; i++)
		if ((*str)[i] == '\t')
			(*str)[i] = ' ';
	i = 0;
	while (**str)
	{
		if (**str == ' ')
		{
			while (*(*str + 1) == ' ')
				(*str)++;
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
	tmp = Clean_string(trimed, 0);
	free(oldBuff);
	return (tmp);
}
