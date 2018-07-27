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
	
	void *(*p_memset)(void *, int, size_t);
	void *(*p_memcpy)(void *, const void *, size_t);
	void *(*p_memchr)(const void *, int, size_t);

	size_t (*p_strlen)(const char *);
	char *(*p_strcpy)(char *, const char *);
	char *(*p_strcat)(char *, const char *);
	int (*p_strcmp)(const char *, const char *);

	void *(*p_malloc)(size_t);
	void (*p_free)(void *);

	int *errno_location;
	char *(*p_strerror)(int);

	int (*p_open)(const char *, int, ...);
	int (*p_close)(int);
	ssize_t (*p_read)(int, void *, size_t);
	ssize_t (*p_write)(int, const void *, size_t);
	off_t (*p_lseek)(int, off_t, int);

	FILE *(*p_fopen)(const char *, const char *);
	int (*p_fclose)(FILE *);
	int (*p_fseek)(FILE *, long, int);
	int (*p_fseeko)(FILE *, __off_t, int);
	long (*p_ftell)(FILE *);
	off_t (*p_ftello)(FILE *);
	int (*p_sprintf)(char *, const char *, ...);
	int (*p_vsnprintf)(char *, size_t, const char *, va_list);
	size_t (*p_fread)(void *, size_t, size_t, FILE *);
	size_t (*p_fwrite)(const void *, size_t, size_t, FILE *);
	int (*p_ferror)(FILE *);

	int (*p_rand)(void);
	
	/* room for later extensions */
	void *unused[33];
};

long zlib_set_imports(struct _zlibslb_funcs *funcs);

#endif
