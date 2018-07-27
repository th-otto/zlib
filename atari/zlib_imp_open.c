/*
 * zlib_imp_open.c - loader for library
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
#include "zlib_imp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <mint/cookie.h>
#include "zlibstruct.h"

static struct _zlibslb_funcs zlibslb_funcs;


typedef struct
{
	long key;
	long value;
} COOKIE;


static COOKIE *get_cookie_jar(void)
{
	return (COOKIE *) Setexc(360, (void (*)()) -1L);
}


static int get_cookie(long key, long *value)
{
	COOKIE *cookiejar = get_cookie_jar();

	*value = 0;
	if (cookiejar)
	{
		while (cookiejar->key)
		{
			if (cookiejar->key == key)
			{
				*value = cookiejar->value;
				return 1;
			}
			cookiejar++;
		}
	}
	return 0;
}


long slb_zlib_open(const char *slbpath)
{
	long ret;
	uLong flags;
	long cpu;
	
	SLB *zlib = slb_zlib_get();
	
	if (!zlib)
		return -EBADF;
	if (zlib->handle)
		return 0;

	/*
	 * the SLB was compiled without -mshort;
	 * since we pass functions pointers back, the application currently
	 * cannot use that, either.
	 * This also prevents this library from being used by e.g Pure-C.
	 */
#ifdef __MSHORT__
# error "using zlib.slb with short ints currently unsupported"
#endif
	if (sizeof(int) != sizeof(long))
		return -EINVAL;
	 
	zlibslb_funcs.struct_size = sizeof(zlibslb_funcs);
	zlibslb_funcs.int_size = sizeof(int),
	zlibslb_funcs.zlib_vernum = ZLIB_VERNUM;
#define S(x) zlibslb_funcs.p_##x = x
	S(memset);
	S(memcpy);
	S(memchr);
	S(strlen);
	S(strcpy);
	S(strcat);
	S(strcmp);
	S(malloc);
	S(free);
	zlibslb_funcs.errno_location = &errno;
	S(strerror);
	S(open);
	S(close);
	S(read);
	S(write);
	S(lseek);
	S(fopen);
	S(fclose);
	S(fseek);
	S(fseeko);
	S(ftell);
	S(ftello);
	S(sprintf);
	S(vsnprintf);
	S(fread);
	S(fwrite);
	S(ferror);
	S(rand);
#undef S
	
	ret = Slbopen(SHAREDLIB, slbpath, ZLIB_VERNUM, &zlib->handle, &zlib->exec);
	if (ret < 0)
		return ret;
	ret = zlib_set_imports(&zlibslb_funcs);
	if (ret < 0)
	{
		slb_zlib_close();
		return ret;
	}
	
	/*
	 * check compile flags; that function should be as simple as to just return a constant
	 * and we can hopefully call it even on mismatched configurations
	 */
	flags = zlibCompileFlags();
	/* basic types should be all 32-bit */
	if ((flags & 0xff) != 0x55)
	{
		slb_zlib_close();
		return -EINVAL;
	}
	get_cookie(C__CPU, &cpu);
	if (cpu >= 20)
	{
		/* should be able to use a 000 library, anyways */
	} else
	{
		if (flags & (1 << 10))
		{
			/* cpu is not 020+, but library was compiled for it */
			slb_zlib_close();
			return -EINVAL;
		}
	}
#if defined(__mcoldfire__)
	/* if cpu is cf, but library was not compiled for it... */
	if (!(flags & (1 << 11)) || cpu > 0)
#else
	/* if cpu is not cf, but library was compiled for it... */
	if (flags & (1 << 11))
#endif
	{
		slb_zlib_close();
		return -EINVAL;
	}
	
	return ret;
}


static long _CDECL slb_unloaded(SLB_HANDLE slb, long fn, short nwords, ...)
{
	(void)slb;
	(void)fn;
	(void)nwords;
	(void) Cconws(SHAREDLIB " was already unloaded\r\n");
	Pterm(1);
	return -32;
}


void slb_zlib_close(void)
{
	SLB *zlib = slb_zlib_get();

	if (!zlib || !zlib->handle)
		return;
	Slbclose(zlib->handle);
	zlib->handle = 0;
	zlib->exec = slb_unloaded;
}
