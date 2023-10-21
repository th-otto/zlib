/*
 * strcpy.c
 */

#include <string.h>

char *strcpy(char *dst, const char *src)
{
	char *ptr = dst;

	while ((*dst++ = *src++) != '\0')
		;
	return ptr;
}
