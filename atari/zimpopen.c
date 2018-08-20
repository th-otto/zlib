/*
 * zlib_imp_open.c - loader for library
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
#include "slb/zlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <mint/cookie.h>
#include <mint/mintbind.h>
#include "zlibstr.h"
#include "slbload.h"

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


#if defined(__MSHORT__) || defined(__PUREC__) || defined(__AHCC__)

static void *_CDECL gcc_memset(void *s, z_int_t val, size_t len)
{
	return memset(s, (int)val, len);
}

static void *_CDECL gcc_memcpy(void *d, const void *s, size_t len)
{
	return memcpy(d, s, len);
}

static void *_CDECL gcc_memchr(const void *s, z_int_t val, size_t len)
{
	return memchr(s, (int)val, len);
}

static size_t _CDECL gcc_strlen(const char *s)
{
	return strlen(s);
}

static char *_CDECL gcc_strcpy(char *d, const char *s)
{
	return strcpy(d, s);
}

static char *_CDECL gcc_strcat(char *d, const char *s)
{
	return strcat(d, s);
}

static z_int_t _CDECL gcc_strcmp(const char *d, const char *s)
{
	return strcmp(d, s);
}

static void *_CDECL gcc_malloc(size_t s)
{
	return malloc(s);
}

static void _CDECL gcc_free(void *s)
{
	free(s);
}

#if defined(__PUREC__) || defined(__AHCC__)
#define ESRCH	3	    /* No such process            */
#define EINTR	4		/* Interrupted system call    */
#define ENXIO	6		/* No such device or address  */
#define EFAULT	14		/* Bad address                */
#define ENOTBLK	15		/* Bulk device required       */
#define EBUSY	16		/* Resource is busy           */
#define ENOTTY	25		/* Not a terminal             */
#define ETXTBSY	26		/* Text file is busy          */
#define EFBIG	27		/* File is too large          */
#define EMLINK	31		/* Too many links             */
#define EPIPE	32		/* Broken pipe                */
#define EILSEQ  84      /* Illegal byte sequence      */
#endif

static z_int_t _CDECL gcc_get_errno(void)
{
#if defined(__GNUC__) || defined(_GNU_SOURCE)
	/* we are just here because of -mshort */
	return errno;
#elif defined(__PUREC__) || defined(__AHCC__) || defined(LATTICE)
	/* must translate error numbers from Pure-C library to what mintlib expects */
	switch (errno)
	{
		case EPERM: return 38;
		case ENOENT: return 33;
		case ESRCH: return 20;
		case EINTR: return 128;
		case EIO: return 90;
		case ENXIO: return 46;
		case EBADF: return 37;
#if defined(__PUREC__) || defined(__AHCC__)
		case EILLSPE: return 25; /* -> EINVAL */
		case EINVMEM: return 40; /* -> EFAULT */
#endif
		case EFAULT: return 40;
		case ENOTBLK: return 23;
		case EBUSY: return 2;
		case ENOMEM: return 39;
		case EACCES: return 36;
		case EEXIST: return 85;
#if defined(__PUREC__) || defined(__AHCC__)
		case EPLFMT: return 66; /* -> ENOEXEC */
#endif
#if defined(LATTICE)
		case ENOEXEC: return 66;
		case EAGAIN: return 326;
		case EXDEV: return 48;
		case ECHILD: return 48;
#endif
		case ENODEV: return 15;
		case ENOTDIR: return 34;
		case EINVAL: return 25;
		case ENFILE: return 50;
		case EMFILE: return 35;
		case ENOTTY: return 87;
		case ETXTBSY: return 70;
		case EFBIG: return 71;
		case ENOSPC: return 91;
		case ESPIPE: return 6;
		case EROFS: return 13;
		case EMLINK: return 82;
		case EPIPE: return 81;
		case EDOM: return 89;
		case ERANGE: return 88;
#if defined(__PUREC__) || defined(__AHCC__)
		case ENMFILE: return 49;
#endif
#if defined(LATTICE)
		case EDEADLK: return 22;
#endif
		case EILSEQ: return 27;
	}
	return 1;
#else
 # error "NYI"
	return 1;
#endif
}

static char *_CDECL gcc_strerror(z_int_t e)
{
#if defined(__GNUC__) || defined(_GNU_SOURCE)
	return strerror((int)e);
#else
	/* FIXME: would need strerror from mintlib */
	static char errorbuf[14];
	sprintf(errorbuf, "error #%d", (int)e);
	return errorbuf;
#endif
}

#define MINTLIB_O_CREAT  0x000200L
#define MINTLIB_O_TRUNC  0x000400L
#define MINTLIB_O_APPEND 0x001000L
#define MINTLIB_O_EXCL   0x000800L

static z_int_t _CDECL gcc_open(const char *filename, z_int_t access, ...)
{
	va_list args;
	int real_access;
	mode_t mode = 0644;
	
	va_start(args, access);
	if (access & MINTLIB_O_CREAT)
		mode = va_arg(args, z_int_t);
	va_end(args);
	real_access = (int)access & O_ACCMODE; /* these are identical */
	if (access & MINTLIB_O_CREAT)
		real_access |= O_CREAT;
	if (access & MINTLIB_O_TRUNC)
		real_access |= O_TRUNC;
	if (access & MINTLIB_O_APPEND)
		real_access |= O_APPEND;
	if (access & MINTLIB_O_EXCL)
		real_access |= O_EXCL;
	/* others are not use by zlib/gz_open */
	return open(filename, real_access, mode);
}

static z_int_t _CDECL gcc_close(z_int_t fd)
{
	return close((int)fd);
}

static ssize_t _CDECL gcc_read(z_int_t fd, void *buf, size_t len)
{
	return read((int)fd, buf, len);
}

static ssize_t _CDECL gcc_write(z_int_t fd, const void *buf, size_t len)
{
	return write((int)fd, buf, len);
}

static off_t _CDECL gcc_lseek(z_int_t fd, off_t off, z_int_t whence)
{
	return lseek((int)fd, off, (int)whence);
}

static FILE *_CDECL gcc_fopen(const char *fname, const char *mode)
{
	return fopen(fname, mode);
}

static z_int_t _CDECL gcc_fclose(FILE *fp)
{
	return fclose(fp);
}

static z_int_t _CDECL gcc_fseek(FILE *fp, long off, z_int_t whence)
{
	return fseek(fp, off, (int)whence);
}

static z_int_t _CDECL gcc_fseeko(FILE *fp, __off_t off, z_int_t whence)
{
	return fseek(fp, off, (int)whence);
}

static long _CDECL gcc_ftell(FILE *fp)
{
	return ftell(fp);
}

static __off_t _CDECL gcc_ftello(FILE *fp)
{
	return ftell(fp);
}

static z_int_t _CDECL gcc_sprintf(char *buf, const char *format, ...)
{
	va_list args;
	int ret;
	va_start(args, fmt);
	ret = vsprintf(buf, format, args);
	va_end(args);
	return ret;
}

static z_int_t _CDECL gcc_vsnprintf(char *buf, size_t len, const char *format, va_list args)
{
	(void)len;
	return vsprintf(buf, format, args);
}

static size_t _CDECL gcc_fread(void *buf, size_t size, size_t count, FILE *fp)
{
	return fread(buf, size, count, fp);
}

static size_t _CDECL gcc_fwrite(const void *buf, size_t size, size_t count, FILE *fp)
{
	return fwrite(buf, size, count, fp);
}

static z_int_t _CDECL gcc_ferror(FILE *fp)
{
	return ferror(fp);
}

static z_int_t _CDECL gcc_rand(void)
{
	return rand();
}

#define S(x) zlibslb_funcs.p_##x = gcc_##x

#else

static z_int_t _CDECL get_errno(void)
{
	return errno;
}

#define S(x) zlibslb_funcs.p_##x = x
#endif


long slb_zlib_open(const char *slbpath)
{
	long ret;
	unsigned long flags;
	long cpu;
	
	SLB *zlib = slb_zlib_get();
	
	if (!zlib)
		return -EBADF;
	if (zlib->handle)
		return 0;

	zlibslb_funcs.struct_size = sizeof(zlibslb_funcs);
	zlibslb_funcs.int_size = sizeof(z_int_t);
	if (zlibslb_funcs.int_size != sizeof(long))
		return -EINVAL;
	zlibslb_funcs.zlib_vernum = ZLIB_VERNUM;
	S(memset);
	S(memcpy);
	S(memchr);
	S(strlen);
	S(strcpy);
	S(strcat);
	S(strcmp);
	S(malloc);
	S(free);
	S(get_errno);
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
	
	ret = slb_load(SHAREDLIB, slbpath, ZLIB_VERNUM, &zlib->handle, &zlib->exec);
	if (ret < 0)
		return ret;

	/*
	 * check compile flags; that function should be as simple as to just return a constant
	 * and we can hopefully call it even on mismatched configurations
	 */
	flags = zlib_slb_control(0, 0);
	get_cookie(C__CPU, &cpu);
	if (cpu >= 20)
	{
		/* should be able to use a 000 library, anyways */
	} else
	{
		if (flags & (1L << 16))
		{
			/* cpu is not 020+, but library was compiled for it */
			slb_zlib_close();
			return -EINVAL;
		}
	}
#if defined(__mcoldfire__)
	/* if cpu is cf, but library was not compiled for it... */
	if (!(flags & (1L << 17)) || cpu > 0)
#else
	/* if cpu is not cf, but library was compiled for it... */
	if (flags & (1L << 17))
#endif
	{
		slb_zlib_close();
		return -EINVAL;
	}
	
	ret = zlib_slb_control(1, &zlibslb_funcs);
	if (ret < 0)
	{
		slb_zlib_close();
		return ret;
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
	slb_unload(zlib->handle);
	zlib->handle = 0;
	zlib->exec = slb_unloaded;
}
