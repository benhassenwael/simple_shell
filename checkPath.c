#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/**
* check_sys_directories - loop throw the array of directories already created,
* concatiate the strig given as if is name of the program to execute
* than test with stat if it exist we return the real path
* @name: each string give by the user
* @env: var env
* @arrPATH: array of (path directories)
* @GC: garbage collector
*
* Return: char *
*/
char *check_sys_directories(char *name, char **env, char *arrPATH[], gc *GC)
{
	char *newArrPATH[10], *path = NULL;
	int i = 0;
	struct stat st;


	while (arrPATH[i])
	{
		newArrPATH[i] = _strConcatEnv(arrPATH[i], name, '/', GC);
		if (stat(newArrPATH[i], &st) == 0)
			return (newArrPATH[i]);
		i++;
	}
	/* if we dont find it in the hole directories we retunr NULL */
	return (NULL);
}

/**
* checkNameProg - check if the name of the command given is a name of a program
* of any of the directories of the variable $PATH if not do an other check with
* check_sys_directories and return the real path of the program
* @name: name given
* @env: env variables
* @GC: garbage collector
*
* Return: real path of the program
*/

char *checkNameProg(char *name, char **env, gc *GC)
{

	char *arrPATH[10], *tmp = NULL, *PATHval = NULL, *path = NULL;
	int i = 0;
	struct stat st;

	PATHval = _getenv("PATH", env);

	if (!name || *name == '\0')
		return (NULL);
	/* arrPATH is null terminated */
	while (1)
	{
		tmp = _strparse(&PATHval, ":");
		arrPATH[i] = _copAlloc(tmp, GC);
		if (!arrPATH[i])
			break;
		i++;
	}
	if (stat(name, &st) != 0)
	{
		path = check_sys_directories(name, env, arrPATH, GC);
		if (path)
			return (path);
	}
	else
	{
		/* it work correctly */
		return (name);
	}
	return (NULL);
}

/**
* lunch_prog - create a new pid for the child lunch the program, make the
* parent (shell) waits for the return value of the exist status
* @command: command path
* @args: array of args, (even if args[0] = "ls" not "/bin/ls" it would work)
* 	because command is the full path
* @env: env var
*
* Return: 0
* Error: some thing else
*/

int lunch_prog(char *command, char **args, char **env)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork didnt work");
		return (-2);
	}
	else if (pid == 0)
	{
		/* child process */
		status = execve(command, args, env);
		if (status == -1)
		{
			perror("command didnt work");
			exit(-1);
		}
		exit (0);

	}
	else
	{
		waitpid(pid, &status, 0);
		printf(" leasable status  = %d\n", WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

/**
* main - check for command name
* @ac: nb of arguments
* @av: arguments
* @env: env
* Return: 0
* Error: 1
int main(int ac, char **av, char **env)
{
	gc GC;
	int status = 0;
	unsigned int i;
	struct stat st;
	char *path = NULL;
	char *str = "ls";
	char *arg[] = {"nnnnnnnnn", "-i"};
	char **FullCommand;

	GC.str_coll = malloc(sizeof(gc) * 1024);
	GC.length = 0;
	path = checkNameProg(str, env, &GC);
	if (path)
	{
		status = lunch_prog(path, arg, env);
		free_Garbage_coll(&GC);
		return (status);
	}
	else
	{
		free_Garbage_coll(&GC);
		return (-1);
	}
}
*/
