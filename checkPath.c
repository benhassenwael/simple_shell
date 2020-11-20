#include "simple_shell.h"
#include <sys/stat.h>

/**
* X - 
* @a: 
*
* Return:
*/

char *simple_concat(char *str, char *cop)
{
	char buf[500];

	return (NULL);
}

/**
* checkNameProg - check if the name of the command given is a name of a program
* of any of the directories of the variable $PATH
* @name: name given
*
* Return:
*/
	
int checkNameProg(char *name, char **env)
{

	char *repos[500], *PATHval = NULL, *rep = NULL ;
	int i = 0;

	PATHval = _getenv("PATH", env);
	while (repos[i])
	{
		rep = _strparse(repos, " ");
		repos[i] = simple_concat(rep, name);
	}


	return (0);
}



/**
* main - 
* @argc: nb of arguments
* @argv: arguments
*
* Return: 0
* Error: 1
*/
int main(int ac, char **av, char **env)
{
    unsigned int i;
    struct stat st;


    char *str = "ls";

    checkNameProg(str, env);
    /*
    if (ac < 2)
    {
        printf("Usage: %s path_to_file ...\n", av[0]);
        return (1);
    }
    i = 1;
    while (av[i])
    {
        printf("%s:", av[i]);
        if (stat(av[i], &st) == 0)
        {
            printf(" FOUND\n");
        }
        else
        {
            printf(" NOT FOUND\n");
        }
        i++;
    }
    */
    return (0);
}
