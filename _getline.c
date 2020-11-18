#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

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
	int i;

	for (i = 0; i < n; i++)
		if (arr[i] == '\n')
			return (arr + i);
	return (NULL);
}

/**
 * _getline - reads a line from given file descriptor and stored in *lineptr
 * the line includes the newline character and is null-terminated
 * *lineptr should be freed by the user program even if _getline() failed
 * @lineptr: can contain a pointer to allocated buffer
 * @n: size of lineptr
 * @fd: file descriptor to read from
 *
 * Return: -1 on failure and line size on success
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	char buffer[1024], *newline_ptr = NULL;
	ssize_t nread;
	int err, i, j, line_size = 0, nwSize;

	fflush(stdout);
	do {
		nread = read(fd, buffer, 1023);
		if (nread == 0 && line_size == 0)
			return (-1);
		newline_ptr = find_newline(buffer, nread);
		if (newline_ptr == NULL)
		{
			err = copy_buffer(buffer, lineptr, line_size, nread);
			if (err == -1)
				return (-1);
			line_size += nread;
		}
	} while (!newline_ptr && nread == 1023);
	buffer[nread] = '\0';
	err = copy_buffer(buffer, lineptr, line_size, nread + 1);
	if (err == -1)
		return (-1);
	*n = line_size + nread;
	return (*n);
}
