#include <errno.h>
#include <stdio.h>

/* Return non-zero if STREAM has its error indicator set.  */
int ferror(FILE *stream)
{
	(void) stream;
	return 0;
}
