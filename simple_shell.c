#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *
 */
int main(int argc, char *argv[], char **env)
{
	char *buffer = NULL;
	size_t n; 
	ssize_t err;
	int fd, i = 0;
	char *str = NULL;
	NewCmd_t *result = NULL;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		//printf("%s$ ", "THE CURRENT DIR");
		err = _getline(&buffer, &n, STDIN_FILENO);
		if (err == -1)
		{
			perror("failed to read command");
			return (-1);
		} else
			printf("your command was: %s", buffer);
		
		result = parseLine(buffer);
		if (result == NULL)
			perror("failed to parseLine");
		else 
		{
			printf(" ------ of ---------- \n");
		}

	}
	/*
	*/
	return (0);
}
