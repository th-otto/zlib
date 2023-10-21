/*
 * free.c
 */

#include <stdlib.h>
#include <mint/osbind.h>

void free(void *param)
{
	Mfree(param);
}
