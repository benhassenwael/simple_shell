#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
* _copAlloc - allocate and copy string
* @str: string
* @GC: gc
* Return: new pointer to allocated string
*/

char *_copAlloc(char *str, gc *GC)
{

	int i = 0;
	char *ptr;

	if (!str || *str == '\0')
		return (NULL);
	for (i = 0; str[i]; i++)
	;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		ptr[i] = str[i];
	}
	ptr[i] = '\0';
	if (GC)
		_insertTo_GC(GC, ptr);

	return (ptr);
}

/**
* _strConcatEnv - concatinate 2 string send with char in between
* if 0 is passed concat only 2 strings
* @str1: name of the envirnment variable
* @cop: the value of the var env
* @ch: char to concat in between
* @newGC: garbage collector pointer to make it easy wen freeing
* Return: pointer to an allocated path
*/

char *_strConcatEnv(char *str1, char *cop, int ch, gc *newGC)
{
	char *path = NULL;
	int len1 = 0, len2 = 0, length = 0, i = 0, j = 0;

	if (!cop)
		cop = "";
	if (!str1)
		return (NULL);
	len1 = _strlen(str1);
	len2 = _strlen(cop);
	length = len1 + len2 + 2;
	path = malloc(sizeof(char) * length);
	if (!path)
		return (NULL);
	for (i = 0, j = 0; i < length && cop[j]; i++)
	{
		if (i < len1)
			path[i] = str1[i];
		else if (i == len1 && ch)
		{
			path[i] = ch;
		}
		else if (i == len1 && !ch)
		{
			path[i] = cop[j];
			j++;
		}
		else
		{
			path[i] = cop[j];
			j++;
		}
	}
	path[i] = '\0';
	if (newGC)
		_insertTo_GC(newGC, path);
	else
		_insertTo_Env_GC(newGC, path);
	return (path);
}


/**
* checkName - check if the Name contain sp char if it does return 2 then check
* if the name sent exist in the ARG (at the start of ARG) if it does return 1
* if it doesnt exist return 0
*
* @Name: name of the env var
* @ARG: the full path of the var env
* @ch: pass 0 if we dont want to search for sp char (if found return 2)
* Return: 1 on found / 0 not found / 2 found sp char
* Error: 0
*/

int checkName(char *Name, char *ARG, char ch)
{
	int i, j, found = 0;


	if (!Name || !ARG || *ARG == '\0')
		return (0);
	if (*Name == '\0')
		return (1);
	for (i = 0; Name[i] && ch; i++)
		if (Name[i] == ch)
			return (2);
	if (ARG[0] && ARG[0] == Name[0])
	{
		for (i = 0; Name[i]; i++)
		{
			for (j = 0; ARG[j] && ARG[j] != '='; j++)
			{
				if (ARG[j] == Name[i + j])
					found = 1;
				else
				{
					found = 0;
					break;
				}
			}
			if (found)
				break;
		}
	}
	if (found)
		return (1);
	else
		return (0);
}



/**
* extractValue - send a pointer to the value of the env var (every thing after
* the '=')
* @Name: var name
* @STR: full path
* Return: pointer to the value of env var
*/

char *extractValue(char *Name, char *STR)
{
	char *ptr = NULL;
	int i = 0;

	if (!Name)
		return (NULL);
	if (!STR)
		return ("nill");
	if (*STR == '\0')
		return ("");

	ptr = STR;
	for (i = 0; STR[i]; i++)
	{
		if (STR[i] == '=')
		{
			i++;
			ptr += i;
		}
	}
	return (ptr);
}

/**
 * _itoa - Convert Integer To Char
 * @n: Int To Convert
 * Return: Char Pointer
 */
char *_itoa(unsigned int n)
{
	int len = 1, i = 0, nb = 0, pw = 1;
	char *s;


	nb = n;
	do {
		pw *= 10;
		nb /= 10;
		len++;
	} while (nb != 0);
	pw /= 10;
	s = malloc(len);
	if (!s)
		return (NULL);
	s[len - 1] = '\0';
	while (n / 10)
	{
		s[i] = (n / pw) + '0';
		n %= pw;
		i++;
		pw /= 10;
	}
	s[i] = (n % 10) + '0';
	return (s);
}



