#include "simple_shell.h"

/**
 * copy_buffer - allocate new size and concatenates given buffer to lineptr
 * @buffer: array of char
 * @lineptr: array of char
 * @line_size: size of lineptr
 * @buffer_size: buffer size
 *
 * Return: 0 on success and -1 on failure
 */
int copy_buffer(char *buffer, char **lineptr,
		size_t line_size, size_t buffer_size)
{
	int i, j, new_size = line_size + buffer_size;
	char *new_line = NULL;

	new_line = _realloc(*lineptr, line_size, sizeof(char) * new_size);
	if (new_line == NULL)
		return (-1);
	*lineptr = new_line;
	for (i = line_size, j = 0; i < new_size; i++, j++)
		(*lineptr)[i] = buffer[j];
	return (0);
}

/**
 * find_newline - loops the given array to find '\n'
 * @arr: array of characters
 * @n: size of the array
 *
 * Return: pointer to the first '\n' found in the array or NULL if none found
 */
char *find_newline(char *arr, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		if (arr[i] == '\n')
			return (arr + i);
	return (NULL);
}

/**
 * _getline - reads a line from given file descriptor and stored in *lineptr
 * the line includes the newline character and is null-terminated
 * *lineptr should be freed by the user program even if _getline() failed
 * @st: pointer to status
 * @GC: gc
 * Return: -1 on failure and line size on success
*/

char *_getline(gc *GC, int *st)
{
	int i, buffsize = 1024, rd;
	char c = 0;
	char *buff = malloc(buffsize);

	if (buff == NULL)
	{
		free(buff);
		return (NULL);
	}

	for (i = 0; c != EOF && c != '\n'; i++)
	{
		fflush(stdin);
		rd = read(STDIN_FILENO, &c, 1);
		if (rd == 0)
			__exit(NULL, GC, NULL, buff, st);
		buff[i] = c;
		if (buff[0] == '\n')
		{
			free(buff);
			return ("\0");
		}

		if (i >= buffsize)
		{
			buffsize += buffsize;
			buff = _realloc(buff, buffsize, (buffsize * 2));
			if (buff == NULL)
			{
				return (NULL);
			}
		}
	}
	buff[i] = '\0';
	return (buff);
}
