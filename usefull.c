#include "simple_shell.h"

/**
* _putchar - print a single char
* @c: char
*
* Return: int
*/

int _putchar(char c)
{
	return (write(1, &c, 1));
}


/**
* _puts - print a string
* @str: string
*
* Return: length of the string
*/

int _puts(char *str)
{
	int i = 0;

	for (i = 0; str[i]; i++)
		_putchar(str[i]);

	return (i);
}

/**
* _strlen - return the length of the string
* @str: string
*
* Return: length
*/

int _strlen(char *str)
{
	int i = 0;

	for (i = 0; str[i]; i++)
	;
	return (i);
}
/**
* _printArrayOfStrings - print all string in an 2D array and return the nb of
* words
* @ptr: pointer to an array of strings
* @length: length
* Return: length
*/

int _printArrayOfStrings(char **ptr, int length)
{
	int i = 0;


	for (i = 0; ptr[i]; i++)
	{
		_putchar(i + '0');
		_putchar('/');
		_putchar(' ');
		_puts(ptr[i]);
		_putchar('\n');
	}
	_puts("length = ");
	_putchar(i + '0');
	_putchar('\n');
	return (i);
}

