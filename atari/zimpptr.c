/*
 * zlib_imp_ptr.c - return pointer to zlib SLB
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
#include "slb/zlib.h"
#include <stdio.h>
#include <mint/osbind.h>
#include "zlibstr.h"

#ifndef NO_DUMMY_DECL
struct internal_state      {int dummy;}; /* for buggy compilers */
#endif


static long _CDECL slb_not_loaded(SLB_HANDLE slb, long fn, short nwords, ...)
{
	(void)slb;
	(void)fn;
	(void)nwords;
	(void) Cconws(SHAREDLIB " was not loaded\r\n");
	Pterm(1);
	return -32;
}


static SLB zlib_slb = { 0, slb_not_loaded };

SLB *slb_zlib_get(void)
{
	return &zlib_slb;
}
