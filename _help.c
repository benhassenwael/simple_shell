#include "simple_shell.h"

#define HELP_TXT "help: help [BUILTIN]\n    Display "\
"information about builtin commands.\n\n    Displays "\
"brief summaries of builtin commands.  If BUILTIN is\n    specified"\
", gives detailed help on all commands matching BUILTIN,\n    otherwise "\
"the list of help topics is printed.\n\n    Arguments:\n      BUILTIN   "\
"Pattern specifying a help topic\n\n    Exit Status:\n    Returns success "\
"unless BUILTIN is not found or \an invalid option is given.\n"

#define CD_TXT "cd: cd [dir]\n"\
"    Change the shell working directory.\n\n"\
"    Change the current directory to DIR.  The default DIR is the value of \n"\
"    the HOME shell variable.\n\n"\
"    `-' is processed as the previous working directory.\n"\
"    A null directory name is the same as the current directory.\n"\
"    `..' is processed by removing the immediately previous pathname \n"\
"    component back to a slash or the beginning of DIR.\n\n"\
"    Exit Status:\n"\
"    Returns 0 if the directory is changed, and if $PWD "\
"is set successfully;\n    non-zero otherwise.\n"

#define HISTORY_TXT "history: history\n"\
"    Display the history list.\n\n"\
"    Display the history list with line numbers, prefixing each modified\n"\
"    entry with a `*'.\n\n"\
"    Exit Status:\n"\
"    Returns success unless an error occurs.\n"

#define ALIAS_TXT "alias: alias [name[='value'] ... ]\n"\
"    Define or display aliases.\n\n"\
"    Without arguments, `alias' prints the list of aliases in the reusable\n"\
"    form `alias NAME=VALUE' on standard output.\n\n"\
"    Otherwise, an alias is defined for each NAME whose VALUE is given.\n"\
"    A trailing space in VALUE causes the next word to be checked for\n"\
"    alias substitution when the alias is expanded.\n\n"\
"    Exit Status:\n"\
"    alias returns true unless a NAME is supplied for which no alias has been"\
"    defined.\n"

#define SETENV_TXT "setenv: setenv VARIABLE VALUE\n"\
"    Set values of shell environment variable.\n\n"\
"    Change the value of shell variables if VARIABLE already exist\n"\
"    else intialize a new one.\n\n"\
"    Exit Status:\n"\
"    Returns success unless an invalid option is given.\n"

#define UNSETENV_TXT "unsetenv: unsetenv VARIABLE\n"\
"    Unset values of shell environment variable.\n\n"\
"    Exit Status:\n"\
"    Returns success unless an invalid option is given.\n"

#define EXIT_TXT "exit: exit [STATUS]\n"\
"    Exit the shell.\n\n"\
"    Exits the shell with a status of STATUS.  If STATUS is omitted, \n"\
"    the exit status is that of the last command executed.\n"

#define ALL_TXT "help: help [BUILTIN]\n"\
"cd: cd [dir]\n"\
"history: history\n"\
"alias: alias [name[='value'] ... ]\n"\
"setenv: setenv VARIABLE VALUE\n"\
"unsetenv: unsetenv VARIABLE\n"\
"exit: exit [STATUS]\n"

/**
 * str_is_eq - compare two given strings and see if they are the same
 * @str1: first string
 * @str2: second string
 *
 * Return: 1 if both strings are equale and 0 if not
 */
int str_is_eq(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
			return (0);
	}
	if (*str1 != '\0' || *str2 != '\0')
		return (0);
	return (1);
}

/**
 * print_str - print given string to stdrout
 * @str: string to print
 *
 * Return: number of printed characters
 */
int print_str(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		;
	return (write(1, str, i));
}

/**
 * _help - a buit-in function that displays information about
 * built-in commands
 * @args: a null terminated array of arguments
 * @env: environment variables
 * @GC: garbage collector
 *
 * Return: 0 on success and -1 on failure
 */
int _help(char **args, __attribute__((unused))char **env,
		__attribute__((unused))gc * GC)
{
	char *builtin[] = {"cd", "help", "history", "alias",
				"setenv", "unsetenv", "exit"};
	char *txt_arr[] = {CD_TXT, HELP_TXT, HISTORY_TXT, ALIAS_TXT,
				SETENV_TXT, UNSETENV_TXT, EXIT_TXT};
	char *arg;
	int exist = 0, builtin_i, args_i = 1;

	if (args[1] == NULL)
	{
		print_str(ALL_TXT);
		return (0);
	}
	while (args[args_i])
	{
		arg = args[args_i];
		builtin_i = 0;
		while (builtin_i < 7)
		{
			if (str_is_eq(builtin[builtin_i], arg))
			{
				print_str(txt_arr[builtin_i]);
				exist = 1;
			}
			builtin_i++;
		}
		args_i++;
	}
	if (!exist)
	{
		print_str("help: no help topics match\n");
		return (-1);
	}
	return (0);
}
