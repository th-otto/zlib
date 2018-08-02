/*
 * zlibstruct.h - internal header file.
 * List of functions that are imported from the application
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#ifndef __ZLIBSTRUCT_H__
#define __ZLIBSTRUCT_H__ 1

#ifndef _CDECL
#define _CDECL
#endif

struct _zlibslb_funcs {
	/*
	 * sizeof(this struct), as
	 * used by the application.
	 */
	size_t struct_size;
	/*
	 * sizeof of an int of the caller.
	 * As for now, must match the one which
	 * was used to compile the library (32 bit)
	 */
	size_t int_size;
	/*
	 * version of zlib.h the caller used.
	 * As for now, should match the version that was
	 * used to compile the library.
	 */
	long zlib_vernum;
	
	void *_CDECL (*p_memset)(void *, z_int_t, size_t);
	void *_CDECL (*p_memcpy)(void *, const void *, size_t);
	void *_CDECL (*p_memchr)(const void *, z_int_t, size_t);

	size_t _CDECL (*p_strlen)(const char *);
	char *_CDECL (*p_strcpy)(char *, const char *);
	char *_CDECL (*p_strcat)(char *, const char *);
	z_int_t _CDECL (*p_strcmp)(const char *, const char *);

	void *_CDECL (*p_malloc)(size_t);
	void _CDECL (*p_free)(void *);

	z_int_t _CDECL (*p_get_errno)(void);
	char *_CDECL (*p_strerror)(z_int_t);

	z_int_t _CDECL (*p_open)(const char *, z_int_t, ...);
	z_int_t _CDECL (*p_close)(z_int_t);
	ssize_t _CDECL (*p_read)(z_int_t, void *, size_t);
	ssize_t _CDECL (*p_write)(z_int_t, const void *, size_t);
	off_t _CDECL (*p_lseek)(z_int_t, off_t, z_int_t);

	FILE *_CDECL (*p_fopen)(const char *, const char *);
	z_int_t _CDECL (*p_fclose)(FILE *);
	z_int_t _CDECL (*p_fseek)(FILE *, long, z_int_t);
	z_int_t _CDECL (*p_fseeko)(FILE *, __off_t, z_int_t);
	long _CDECL (*p_ftell)(FILE *);
	off_t _CDECL (*p_ftello)(FILE *);
	z_int_t _CDECL (*p_sprintf)(char *, const char *, ...);
	z_int_t _CDECL (*p_vsnprintf)(char *, size_t, const char *, va_list);
	size_t _CDECL (*p_fread)(void *, size_t, size_t, FILE *);
	size_t _CDECL (*p_fwrite)(const void *, size_t, size_t, FILE *);
	z_int_t _CDECL (*p_ferror)(FILE *);

	z_int_t _CDECL (*p_rand)(void);
	
	/* room for later extensions */
	void *unused[33];
};

long _CDECL zlib_slb_control(long fn, void *arg);

#endif
