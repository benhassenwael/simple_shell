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
 * @lineptr: can contain a pointer to allocated buffer
 * @n: size of lineptr
 * @fd: file descriptor to read from
 *
 * Return: -1 on failure and line size on success
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	char buffer[1024], *newline_ptr = NULL;
	ssize_t nread;
	int i, err, line_size = 0;

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
	if (newline_ptr != NULL)
	{
		for (i = 0; buffer[i] != '\n'; i++)
			;
		nread = i + 1;
	}
	err = copy_buffer(buffer, lineptr, line_size, nread + 1);
	if (err == -1)
		return (-1);
	*n = line_size + nread;
	return (*n);
}
*/

/**
 * readline - read from file descriptor line by line
 * @lineptr: pointer to the first returning read string
 * @fd: file descriptor to read from
 *
 * Return: -1 on failure
ssize_t readline(char **lineptr, int fd)
{
	char buffer[1024], c = 0;
	ssize_t nread = 1;
	int i, line_size = 0, lines = 0;

	while (c != EOF && nread != 0)
	{
		fflush(stdin);
		nread = read(fd, &c, 1);
		if (nread == 0 && line_size == 0 && lines == 0)
			return (-1);
		if (c == '\n')
		{
		lineptr[lines] = malloc(sizeof(char) * (line_size + 1));
			for (i = 0; i < line_size; i++)
				lineptr[lines][i] = buffer[i];
			line_size = 0;
			lineptr[lines++][i] = '\0';
			lineptr[lines] = NULL;
		}
		else if (c != EOF)
			buffer[line_size++] = c;
	}
	if (c == EOF && line_size > 1)
	{
		lineptr[lines] = malloc(sizeof(char) * (line_size + 1));
		for (i = 0; i < line_size; i++)
			lineptr[lines][i] = buffer[i];
		line_size = 0;
		lineptr[lines++][i] = '\0';
		lineptr[lines] = NULL;
	}
	return (0);
}
*/


char *_getline(gc *GC)
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
			__exit(NULL, GC, NULL, buff);
		buff[i] = c;
		if (buff[0] == '\n')
		{
			free(buff);
			return ("\0");
		}
		if (i >= buffsize)
		{
			buff = _realloc(buff, buffsize, buffsize + 1);
			if (buff == NULL)
			{
				return (NULL);
			}
		}
	}
	buff[i] = '\0';
	return (buff);
}
