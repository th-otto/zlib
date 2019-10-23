/*
 * slb/zlib.h - Utility functions for the application,
 * when using the shared library.
 *
 * Copyright (C) 2018 Thorsten Otto
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
#ifndef __SLB_ZLIB_H__
#define __SLB_ZLIB_H__ 1

#ifndef ZLIB_SLB
#define ZLIB_SLB 1
#endif

#include <zlib.h>
#include <mint/slb.h>

#if defined(__PUREC__) || defined(__TURBOC__) || defined(__AHCC__)
#undef __CDECL
/* if you get a compile error here, you must turn off ANSI */
#define __CDECL cdecl
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define ZLIB_SHAREDLIB_NAME "zlib.slb"

long slb_zlib_open(const char *slbpath);
void slb_zlib_close(void);
SLB *slb_zlib_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __SLB_ZLIB_H__ */
