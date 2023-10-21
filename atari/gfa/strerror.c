/*
 * strerror.c
 */

#include <string.h>
#include <stdio.h>

#define ERR(s, o) s "\0"
#define NONE
static char const _sys_err_msgs[] = {
	"Unknown error" "\0"
#include "strerror.h"
};


#define ERR(s, o) o,
#define NONE 0,
static unsigned short const _sys_errlist_internal[] = {
#include "strerror.h"
};

#ifndef NO_CONST
#  ifdef __GNUC__
#    define NO_CONST(p) __extension__({ union { const void *cs; void *s; } x; x.cs = p; x.s; })
#  else
#    define NO_CONST(p) ((void *)(p))
#  endif
#endif

/* Map error number to descriptive string.  */

#define SYS_NERR (unsigned int) (sizeof (_sys_errlist_internal) / sizeof (_sys_errlist_internal[0]))

char *strerror(int errnum)
{
	const char *p = &_sys_err_msgs[0];
	if ((unsigned int)errnum < SYS_NERR)
		p += _sys_errlist_internal[errnum];
	return (char *) NO_CONST(p);
}


#ifdef MAIN

#define ERR(s, o) s,
#define NONE 0,
static const char *const _new_sys_errlist_internal[] = {
#include "strerror.h"
};

#undef SYS_NERR
#define SYS_NERR (unsigned int) (sizeof (_new_sys_errlist_internal) / sizeof (_new_sys_errlist_internal[0]))

int main(void)
{
	unsigned int i;
	unsigned int offset = sizeof("Unknown error");
	
	for (i = 0; i < SYS_NERR; i++)
	{
		printf("%u: %u: %s\n", i, offset, _new_sys_errlist_internal[i]);
		if (_new_sys_errlist_internal[i])
			offset += strlen(_new_sys_errlist_internal[i]) + 1;
	}
	return 0;
}
#endif
