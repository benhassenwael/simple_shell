
#include "simple_shell.h"
#include <stdlib.h>

/**
* print_cmd_error - print error
* @args: char **
* @char: name
* @int: counter
*
* Return: void
*/

void print_cmd_error(char *args, char *input, int counter)
{
	char * str = NULL;

	print_str(args);
	print_str(": ");
	str = _itoa(counter);
	print_str(str);
	free(str);
	print_str(": ");
	print_str(input);
	print_str(": not found\n");
}



/**
 * _isalpha - check the code for Holberton School students.
 * @c: blabalbal
 *	
 * Return: Always 0.
 */



int _isalpha(int c)	
{	

	int result = 0;

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		result = 1;
	else
		result = 0;
	return (result);
}

/**
 * _isInteger - check if the char can be an integer.
 * @str: char *
 *
 * Return:  0 / 1
 */



int _isInteger(char *str)
{
	int val = 0, i = 0, alpha = 0;

	if (str[0] == '-')
		return (0);
	while (str[i])
	{

		if (str[i] >= '0' && str[i] <= '9')
		{
			val *= 10;
			val += str[i] - '0';
		}
		else
			alpha = 1;
		i++;
	}
	if (alpha)
		return (0);
	return (val);
}

