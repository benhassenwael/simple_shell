#include "simple_shell.h"

/**
 * free_path_list - free a path list
 * @path_list: null terminated list of paths
 *
 */
void free_path_list(char **path_list)
{
	int i = 0;

	while (path_list[i])
		free(path_list[i++]);
	free(path_list);
}

/**
 * add_to_path_list - reallocate and add a new path to the list
 * @old_array: an array of paths to reallocate
 * @path: path to add to the array
 *
 * Return: newly allocated array of paths null terminated with path
 * added to it or NULL on failure
 */
char **add_to_path_list(char **old_array, char *path)
{
	int size = 0;
	char **list = NULL;

	if (old_array == NULL)
	{
		list = malloc(sizeof(char *) * 2);
		if (list == NULL)
			return (NULL);
		list[0] = path;
		list[1] = NULL;
		return (list);
	}
	while (old_array[size])
		size++;
	list = malloc(sizeof(void *) * (size + 2));
	if (list == NULL)
		return (NULL);
	for (size = 0; old_array[size]; size++)
	{
		list[size] = old_array[size];
	}
	list[size++] = path;
	list[size] = NULL;
	free(old_array);
	return (list);
}

/**
 * get_path_list - break down a given path variable into an array
 * @path_var: path variable
 *
 * Return: array of allocate string for paths in the variable or
 * NULL on failure
 */
char **get_path_list(char *path_var)
{
	int start = 0, end = 0, i;
	char **path_list = NULL, **err_check;
	char *path;

	if (path_var == NULL || *path_var == '\0')
		return (NULL);
	while (path_var[end])
	{
		for (end = start; path_var[end] != ':' && path_var[end]; end++)
		;
		path = malloc(sizeof(char) * ((end - start) + 1));
		if (path == NULL)
		{
			free_path_list(path_list);
			return (NULL);
		}
		i = 0;
		while (start < end)
			path[i++] = path_var[start++];
		path[i] = '\0';
		err_check = add_to_path_list(path_list, path);
		if (err_check == NULL)
		{
			free(path);
			free_path_list(path_list);
			return (NULL);
		}
		path_list = err_check;
		start++;
	}
	return (path_list);
}

/**
 * concat_path - concatenate program name into a full path
 * @path: path to concatenate name to
 * @name: name of the program
 *
 * Return: full path allocated (should be freed) or NULL on failure
 */
char *concat_path(char *path, char *name)
{
	int i, j, size;
	char *full_path = NULL;

	for (size = 0; path[size]; size++)
		;
	for (i = 0; name[i]; size++, i++)
		;
	full_path = malloc(sizeof(char) * (size + 2));
	if (full_path == NULL)
		return (NULL);
	for (i = 0; path[i]; i++)
		full_path[i] = path[i];
	full_path[i++] = '/';
	for (j = 0; name[j]; j++, i++)
		full_path[i] = name[j];
	full_path[i] = '\0';
	return (full_path);
}

/**
 * find_prog_path - get the path of a given program name if it exists
 * @name: program name
 * @env: environment variables list
 *
 * Return: the full program path including the name or NULL if not found
 */
char *find_prog_path(char *name, char **env)
{
	char *path_var = NULL, **path_list = NULL;
	char *prog_path;
	int i;
	struct stat st;

	for (i = 0; name[i]; i++)
	{
		if (name[i] == '/')
			return (name);
	}
	path_var = _getenv("PATH", env);
	if (path_var == NULL)
		return (NULL);
	path_list = get_path_list(path_var);
	if (path_list == NULL)
		return (NULL);
	i = 0;
	while (path_list[i] != NULL)
	{
		prog_path = concat_path(path_list[i], name);
		if (stat(prog_path, &st) == 0)
		{
			free_path_list(path_list);
			return (prog_path);
		}
		free(prog_path);
		i++;
	}
	free_path_list(path_list);
	return (NULL);
}
