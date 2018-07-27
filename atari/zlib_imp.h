/*
 * zlib_imp.h - internal header for building the import library
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
#include "slb/zlib.h"
#include <mint/slb.h>
#include <mint/mintbind.h>
#include <errno.h>
#include "symbols.h"


#undef SLB_NWORDS
#define SLB_NWORDS(_nargs) ((((long)(_nargs) * 2 + 1l) << 16) | (long)(_nargs))
#undef SLB_NARGS
#define SLB_NARGS(_nargs) SLB_NWORDS(_nargs)


#define PUSH_FNQ(fn) \
		" moveq %[fn],%%d1\n" /* push function number */ \
		" move.l %%d1,-(%%a7)\n"

#define PUSH_FNL(fn) \
		" move.l %[fn],-(%%a7)\n" /* push function number */

#define LIBFUNC_(_fn, name, _nargs, pushfn) \
static void __attribute__((used)) __ ## name ## _entry(void) \
{ \
	register SLB *zlib __asm__("a0"); \
 \
	__asm__ __volatile__ ( \
		" .globl " C_SYMBOL_NAME(name) "\n" \
C_SYMBOL_NAME(name) ":\n"); \
 \
	zlib = slb_zlib_get(); \
 \
	__asm__ __volatile__ ( \
		" move.l (%%a7)+,%%d0\n" /* get return pc */ \
		" move.l %[nargs],-(%%a7)\n"  /* push number of args */ \
		pushfn /* push function number */ \
		" move.l (%[zlib]),-(%%a7)\n" /* push SLB handle */ \
		" move.l %%d0,-(%%a7)\n" /* push return pc */ \
		" move.l 4(%[zlib]),%[zlib]\n" /* get exec function */ \
		" jmp (%[zlib])\n"          /* go for it */ \
	: \
	: [zlib]"r"(zlib), [fn]"i"(_fn), [nargs]"i"(SLB_NARGS(_nargs)) \
	: "cc", "memory" \
	); \
	__builtin_unreachable(); \
}

#define LIBFUNC(_fn, name, _nargs) LIBFUNC_(_fn, name, _nargs, PUSH_FNQ(fn))
#define LIBFUNC2(_fn, name, _nargs) LIBFUNC_(_fn, name, _nargs, PUSH_FNL(fn))

#define NOFUNC
