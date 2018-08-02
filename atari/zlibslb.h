/*
 * zlibslb.h - internal header file.
 * Used only when compiling the shared library code,
 * to redirect standard library functions to the
 * library that was linked to the application
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#ifndef __ZLIBSLB_H__
#define __ZLIBSLB_H__ 1

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#undef memset
#undef memcpy
#undef memchr

#undef strlen
#undef strcpy
#undef strcat
#undef strcmp

#undef malloc
#undef free

#undef errno
#undef strerror

#undef open
#undef close
#undef read
#undef write
#undef lseek

#undef fopen
#undef fclose
#undef fseek
#undef fseeko
#undef ftell
#undef ftello
#undef sprintf
#undef vsnprintf
#undef fread
#undef fwrite
#undef ferror

#undef rand

#include "zlibstr.h"

struct _zlibslb_funcs *zlib_get_slb_funcs(void);

#define memset(d, c, l) zlib_get_slb_funcs()->p_memset(d, c, l)
#define memcpy(d, s, l) zlib_get_slb_funcs()->p_memcpy(d, s, l)
#define memchr(d, c, l) zlib_get_slb_funcs()->p_memchr(d, c, l)

#define strlen(s) zlib_get_slb_funcs()->p_strlen(s)
#define strcpy zlib_get_slb_funcs()->p_strcpy
#define strcat zlib_get_slb_funcs()->p_strcat
#define strcmp zlib_get_slb_funcs()->p_strcmp

#define malloc zlib_get_slb_funcs()->p_malloc
#define free zlib_get_slb_funcs()->p_free

#define errno (zlib_get_slb_funcs()->p_get_errno())
#define strerror zlib_get_slb_funcs()->p_strerror

#define open zlib_get_slb_funcs()->p_open
#define close zlib_get_slb_funcs()->p_close
#define read zlib_get_slb_funcs()->p_read
#define write zlib_get_slb_funcs()->p_write
#define lseek zlib_get_slb_funcs()->p_lseek

#define fopen zlib_get_slb_funcs()->p_fopen
#define fclose zlib_get_slb_funcs()->p_fclose
#define fseek zlib_get_slb_funcs()->p_fseek
#define fseeko zlib_get_slb_funcs()->p_fseeko
#define ftell zlib_get_slb_funcs()->p_ftell
#define ftello zlib_get_slb_funcs()->p_ftello
#define sprintf zlib_get_slb_funcs()->p_sprintf
#define vsnprintf zlib_get_slb_funcs()->p_vsnprintf
#define fread zlib_get_slb_funcs()->p_fread
#define fwrite zlib_get_slb_funcs()->p_fwrite
#define ferror zlib_get_slb_funcs()->p_ferror

#define rand zlib_get_slb_funcs()->p_rand

#endif /* __ZLIBSLB_H__ */
