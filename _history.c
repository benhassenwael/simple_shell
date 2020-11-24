#include "simple_shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* toBase10 - convert a positice integer to base 10 unsigned
* @command: command
* @ref: int
* @GC: gc
*
* Return: str
*/

char *toBase10(int ref, gc *GC)
{

	char *bases = "0123456789ABCDEF";
	char *ptr = NULL, *buffer = NULL;
	int len = 0;
	
	buffer = malloc(sizeof(char) * 100);
	if (!buffer)
		return (NULL);
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = bases[ref % 10];
		ref /= 10;
	} while (ref != 0);
	_insertTo_GC(GC, buffer);
	return (ptr);
}

/**
* _Appand_command - appand a line of string given to a file 
* @command: command
* @fileName: fileName
* @GC: gc
*
* Return: 0
* Error: -1
*/

int _Appand_command(char *command, char *fileName, gc *GC)
{

	int fd = 0, writen = 0, len = 0, c = 0, ret = '\n', i = 0, readCh = 0;
	char buff[1000];
		
	fd = open(fileName, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd < 0)
		return (-1);
	if (!command)
	{
		close(fd);
		return (-1);
	}
	len = _strlen(command);

	
	writen = write(fd, command, len);
	printf(" writen = %d\n", writen);
	if (writen != len)
		return (-1);
	close(fd);
	return (0);
}

/**
* X - 
* @a: 
*
* Return:
*/

int appand_newLine(int fd)
{
	int writen = 0, len = 0, c = 0, ret = '\n', i = 0, readCh = 0;
	
	readCh = read(fd, &c, 1);
	printf(" readCh1 = %d\n", readCh);
	printf(" c = %d\n", c);
	while (readCh)
	{
		readCh = read(fd, &c, 1);
		printf(" readCh2 = %d\n", readCh);
		printf(" c = %d\n", c);
		if (readCh == 0)
		{
			writen = write(fd, &ret, 1);
			if (writen < 0)
			{
				printf("err writen   \n" );
				return (-1);
			}
			/*
			*/
		}
		
	};
	return (0);
}
/**
* create_Ref_to_Command - create_Ref_to_Command and appand it to the file given
* concatinate the int and the command given in format "xxx yyyyyyyyyyyyyyy"
* @str: command
* @ref: nb of command set by user
* @GC: gc
*
* Return: 0
* Error: -1
*/

int create_Ref_to_Command(char *str, int ref, char *fileName, gc *GC)
{
	char *reference = NULL;
	char *fsConcat = NULL;
	int ret = 0;

	if (!str || ref < 0)
		return (-1);

	reference = toBase10(ref, GC);
	if (!reference)
		return (-1);
	fsConcat = _strConcatEnv(reference, str, ' ', GC);
	if (!fsConcat)
		return (-1);
	ret = _Appand_command(fsConcat, fileName, GC);
	if (ref < 0)
		return (-1);
	free_noInUse_GC(GC);
	return (0);
}

/**
* read_textfile - read file and print every char until we reach arg letters
* @filename: filename
* @letters: nb of char we are printing
* Return: nbof char printed
*/

ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t nbCharLu = 0, printedChar = 0;
	int fileNumber, i;
	char content[10000];

	if (!filename)
		return (0);

	fileNumber = open(filename, O_RDONLY, 600);
	if (fileNumber == -1)
		return (0);

	nbCharLu = read(fileNumber, content, letters);
	close(fileNumber);

	content[letters] = '\0';
	for (i = 0; content[i]; i++)
	;
	printedChar = write(STDOUT_FILENO, content, i);
	if (printedChar != nbCharLu)
		return (0);
	return (printedChar);
}
/**
* X - 
* @a: 
*
* Return:
*/

int _history(char **args, char **env, gc *GC)
{
	int fd = 0, readCh = 0, writeCh = 0, cl = 0;
	char buf[1024];

	fd = open("./his", O_RDONLY, 0600);

	if (fd < 0)
		return (-1);;
	readCh = 1;
	while (readCh > 0)
	{
		readCh = read(fd, buf, 1024);
		if (readCh < 0)
			return (-1);;
		if (readCh > 0)
		{
			writeCh = write(STDOUT_FILENO, buf, readCh);
			if (writeCh < 0)
				return (-1);;
		}
	}
	cl = close(fd);
	if (cl < 0)
		return (-1);;
	cl = close(fd);
	if (cl < 0)
		return (-1);;
	return (0);
}
/**
* main - 
* @argc: nb of arguments
* @argv: arguments
*
* Return: 0
* Error: 1
int main(int argc, char *argv[])
{
	char *str = "ls -l &&     echo -e";
	char *ptr = NULL;
	gc GC;
	GC.str_coll = malloc(1024);
	GC.length = 0;
	create_Ref_to_Command(str, 941, "./his", &GC);

	_history(argv, argv, &GC);
	//free(GC.str_coll);
	return (0);
}
*/
