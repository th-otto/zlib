/*
 * strlen.c
 */

#include <string.h>

size_t strlen(const char *s)
{
	const char *start = s;

	while (*s++)
		;

	return s - start - 1;
}
