#include <stddef.h>	/* for size_t */
#include <stdlib.h>
#include <string.h>
#include <mint/osbind.h>

void *malloc(size_t n)
{
	return (void *) Malloc(n);
}
