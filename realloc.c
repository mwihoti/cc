#include "main.h"

/**
 * *_memorybyte - fills memmory with byte
 * @s: pointer to memory area
 * @b: byte to fill *s
 * @n: amount of byte to be filled
 *
 * Return: pointer to s memory area
 */
char *_memorybyte(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		s[k] = b;
	return (s);
}

/**
 * strfree - frees a string of strings
 * @ss: string of string
 */
void strfree(char **ss)
{
	char **s = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(s);
}

/**
 * _memoryrealloc - reallocates a block of memory
 * @ptr: pointer to previous mallocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer ptr
 */
void *_memoryrealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	s = malloc(new_size);
	if (!s)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (s);
}
