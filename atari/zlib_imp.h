/*
 * zlib_imp.h - internal header for building the import library
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
#include <mint/mintbind.h>
#include <mint/slb.h>
#include <errno.h>
#include "symbols.h"

SLB *slb_zlib_get(void);

#undef SLB_NWORDS
#define SLB_NWORDS(_nargs) ((((long)(_nargs) * 2 + 1l) << 16) | (long)(_nargs))
#undef SLB_NARGS
#define SLB_NARGS(_nargs) SLB_NWORDS(_nargs)

#ifndef NO_DUMMY_DECL
struct internal_state      {int dummy;}; /* for buggy compilers */
#endif

#ifdef __GNUC__

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

#endif /* __GNUC__ */

#ifdef __PUREC__

static void *jmp_a0(void *) 0x4ed0;
static long move_l_a7_d1(void *, long) 0x221f;
static long move_l_a7_a1(void *, long) 0x225f;
static long push_d0(long) 0x2f00;
static long push_d1(long, long) 0x2f01;
static void *push_a0(long) 0x2f10;
static void *push_a1(void *) 0x2f09;
static void *move_4_a0_1(void *) 0x0004;
static void *move_4_a0_2(void *) 0x2068;

#define LIBFUNC(_fn, name, _nargs) \
void name(void) \
{ \
	jmp_a0(push_a1(move_4_a0_1(move_4_a0_2(push_a0(push_d0(push_d1(move_l_a7_a1(slb_zlib_get(), _fn), SLB_NARGS(_nargs)))))))); \
}
#define LIBFUNC2(_fn, name, _nargs) LIBFUNC(_fn, name, _nargs)

#endif

#define NOFUNC
