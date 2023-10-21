/*
 * memcpy.c/memmove.c
 */

#include <stdlib.h>
#include <string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *pd = (unsigned char *)dest;
	const unsigned char *ps = (const unsigned char *)src;
#if 0
	if (pd > ps)
	{
		for (pd += n, ps += n; n--;)
			*--pd = *--ps;
	} else if (pd < ps)
#endif
	{
		while (n--)
			*pd++ = *ps++;
	}
	return dest;
}
