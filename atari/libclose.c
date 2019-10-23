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



static long __CDECL slb_unloaded(SLB_HANDLE slb, long fn, short nwords, ...)
{
	(void)slb;
	(void)fn;
	(void)nwords;
	(void) Cconws(ZLIB_SHAREDLIB_NAME " was already unloaded\r\n");
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
