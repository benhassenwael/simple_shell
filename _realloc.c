#include "simple_shell.h"
/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to memory to reallocate
 * @old_size: size of memory to reallocate
 * @new_size: new memory size
 *
 * Return: pointer to the new memory or NULL on failure
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_char_ptr;
	char *old_char_ptr;
	cmd_t *new_cmd_ptr;
	cmd_t *old_cmd_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	else if (new_size == 0)
	{
	//	free(ptr);
		return (NULL);
	}
	old_char_ptr = ptr;
	new_char_ptr = malloc(new_size);
	if (new_char_ptr == NULL)
		return (NULL);
	for (i = 0; i < new_size && i < old_size; i++)
	{
		new_char_ptr[i] = old_char_ptr[i];
	}
	//free(old_char_ptr);
	return (new_char_ptr);

}
