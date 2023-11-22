/*
 * Copyright (c) Draconis Internet Package Project
 * Jens Heitmann <jh_draconis@users.sourceforge.net>
 * 
 * This software is licenced under the GNU Public License.
 * Please see COPYING for further information.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA.
 * or have a look to http://www.gnu.org.
 * 
 * Author: Jens Heitmann
 * Version-Date: 2007-07-15
 * 
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mint/slb.h>
#include <mint/osbind.h>
#include <mint/mintbind.h>
#include <mint/basepage.h>
#include <mint/cookie.h>
#include "slbload.h"


/* just in case; we need the TOS error codes here */
#undef E_OK
#undef EBADARG
#undef ENOSYS
#undef EPLFMT
#define E_OK	  0					/* OK, no error */
#define ENOSYS  -32					/* function not implemented */
#define EBADARG	-64					/* range error */
#define EPLFMT	-66					/* invalid program load format */


/* Prototype of SLBExec function */
#ifndef NO_LOCAL_SLB
long __slb_local_exec(void *slb, ...);
#endif

#ifdef __GNUC__
#define _BasPag _base
#endif

static int os_slb = 1;
static const char *user_slbpath;

typedef struct
{
	long magic;
	const char *name;
	long version;
	long flags;
	void __CDECL (*slb_init) (void);
	void __CDECL (*slb_exit) (void);
	void __CDECL (*slb_open) (BASEPAGE *);
	void __CDECL (*slb_close) (BASEPAGE *);
	const char *const *procnames;
	long next; /* used by MetaDOS */
	BASEPAGE *my_bp; /* used by us */
	long reserved[6];
	long num_funcs;
	/* long funcs_table[]; */
} SLB_HEADER;


#ifndef __mcoldfire__
#ifdef __GNUC__
static long asm_invalidate_cache_030(void)
{
	__asm__ __volatile__(
		"\t.dc.w 0x4e7a,2\n"			/* movec	cacr,d0 */
		"\tori.w	#0x808,%%d0\n"		/* cd/ci bit (clear d/i-cache) */
		"\t.dc.w 0x4e7b,2\n"			/* movec	d0,cacr */
	: : : "d0", "cc", "memory");
	return 0;
}


static long asm_invalidate_cache_040(void)
{
	__asm__ __volatile__(
		"\tnop\n"						/* fix for some broken 040s */
		"\t.dc.w 0xf4f8\n"				/* cpusha bc; flush to memory */
		"\t.dc.w 0xf4d8\n"				/* cinva bc; invalidate */
	: : : "d0", "cc", "memory");
	return 0;
}
#endif


#ifdef __PUREC__
static void asm_invalidate_cache_030_1(void) 0x4e7a;
static void asm_invalidate_cache_030_2(void) 0x0002;
static void asm_invalidate_cache_030_3(void) 0x0040;
static void asm_invalidate_cache_030_4(void) 0x0808;
static void asm_invalidate_cache_030_5(void) 0x4e7b;
static void asm_invalidate_cache_030_6(void) 0x0002;

static long asm_invalidate_cache_030(void)
{
	asm_invalidate_cache_030_1();
	asm_invalidate_cache_030_2();
	asm_invalidate_cache_030_3();
	asm_invalidate_cache_030_4();
	asm_invalidate_cache_030_5();
	asm_invalidate_cache_030_6();
	return 0;
}

static void asm_invalidate_cache_040_1(void) 0x4e71;
static void asm_invalidate_cache_040_2(void) 0xf4f8;
static void asm_invalidate_cache_040_3(void) 0xf4d8;

static long asm_invalidate_cache_040(void)
{
	asm_invalidate_cache_040_1();
	asm_invalidate_cache_040_2();
	asm_invalidate_cache_040_3();
	return 0;
}

#endif


static long get_cpu(void)
{
	long *jar;

	jar = (long *)Setexc(0x5a0 / 4, (void (*)(void))-1);
	if (jar)
	{
		while (jar[0] != 0)
		{
			if (jar[0] == C__CPU)
				return jar[1];
			jar += 2;
		}
	}
	return 0;
}


static void asm_invalidate_cache(void)
{
	long cpu;

	cpu = get_cpu();
	if (cpu >= 40)
		Supexec(asm_invalidate_cache_040);
	else if (cpu >= 30)
		Supexec(asm_invalidate_cache_030);
}
#endif


#ifndef NO_LOCAL_SLB
#pragma GCC diagnostic ignored "-Warray-bounds"
static long localSlbLoad(const char *sharedlib, const char *path, long ver, SLB_HANDLE *slb, SLB_EXEC *slbexec)
{
	long *exec_longs;
	char file[256];
	BASEPAGE *bp;
	SLB_HEADER *slbheader;
	size_t j, len;
	int i;

	if (path)
	{
		len = strlen(path);
		strcpy(file, path);

		for (j = 0; j < len; j++)
			if (file[j] == '/')
				file[j] = '\\';
		if (file[len - 1] != '\\')
			strcat(file, "\\");
	} else
	{
		file[0] = 0;
	}
	
	strcat(file, sharedlib);

	bp = (BASEPAGE *) Pexec(3, file, "\0", 0L);
	for (i = 0; i < 2 && (long) bp < 0; i++)
	{
		const char *ptr;
		const char *slb_path;

		if (i == 0)
		{
			slb_path = user_slbpath;
		} else
		{
			slb_path = getenv("SLBPATH");
			if (slb_path == NULL)
				slb_path = "C:\\mint\\slb";
		}
		
		if (slb_path != NULL)
		{
			while (slb_path[0])
			{
				ptr = strchr(slb_path, ';');
				if (!ptr)
					ptr = slb_path + strlen(slb_path);

				strncpy(file, slb_path, ptr - slb_path);
				file[ptr - slb_path] = 0;
				len = strlen(file);
				while (len && (file[len - 1] == ' ' || file[len - 1] == '\t'))
					file[--len] = 0;

				for (j = 0; j < len; j++)
					if (file[j] == '/')
						file[j] = '\\';
				if (file[len - 1] != '\\')
					strcat(file, "\\");

				strcat(file, sharedlib);
				bp = (BASEPAGE *) Pexec(3, file, "\0", 0L);
				if ((long) bp > 0)
				{
					break;
				}
				slb_path = ptr;
				while (*slb_path == ' ' || *slb_path == '\t' || *slb_path == ';')
					slb_path++;
			}
		}
	}

	if ((long) bp <= 0)
		return (long) bp;

	if (bp->p_env)
	{
		Mfree(bp->p_env);
		bp->p_env = 0;
	}

	/*
	 * CT60 TOS is broken, and does not always invalidate the cache on Pexec(3,...)
	 * Older FreeMiNT kernels are broken, too
	 */
#ifndef __mcoldfire__
	asm_invalidate_cache();
#endif

	/* Test for the new programm-format */
	exec_longs = (long *) ((char *) bp->p_tbase);
	if ((exec_longs[0] == 0x283a001aL && exec_longs[1] == 0x4efb48faL) ||	/* Original binutils */
		(exec_longs[0] == 0x203a001aL && exec_longs[1] == 0x4efb08faL))     /* binutils >= 2.18-mint-20080209 */
	{
		slbheader = (SLB_HEADER *) ((char *) bp->p_tbase + 228L);
	} else if ((exec_longs[0] & 0xffffff00L) == 0x203a0000L &&              /* binutils >= 2.41-mintelf */
		exec_longs[1] == 0x4efb08faUL &&
		/*
		 * 40 = (minimum) offset of elf header from start of file
		 * 24 = offset of e_entry in common header
		 * 30 = branch offset (sizeof(GEMDOS header) + 2)
		 */
		(exec_longs[0] & 0xff) >= (40 + 24 - 30))
	{
		long elf_offset;
		long e_entry;
		
		elf_offset = (exec_longs[0] & 0xff);
		e_entry = *((long *)((char *)bp->p_tbase + elf_offset + 2));
		slbheader = (SLB_HEADER *) ((char *) bp->p_tbase + e_entry);
	} else
	{
		slbheader = (SLB_HEADER *) (bp->p_tbase);
	}

	if (slbheader->magic != 0x70004afcL)
	{
		Mfree(bp);
		return EPLFMT;
	}

	if (slbheader->version < ver)
	{
		Mfree(bp);
		return EBADARG;
	}

	Mshrink(bp, sizeof(BASEPAGE) + bp->p_tlen + bp->p_dlen + bp->p_blen);
	if (strlen(file) > 127)
		file[127] = 0;
	strcpy(bp->p_cmdlin, file);

	slbheader->my_bp = bp;

	slbheader->slb_init();
	slbheader->slb_open(_BasPag);

	*slb = (SLB_HANDLE) slbheader;
	*slbexec = (SLB_EXEC) __slb_local_exec;
	return E_OK;
}
#pragma GCC diagnostic warning "-Warray-bounds"

static long localSlbUnload(SLB_HANDLE slb)
{
	((SLB_HEADER *) slb)->slb_close(_BasPag);
	((SLB_HEADER *) slb)->slb_exit();

	Mfree(((SLB_HEADER *) slb)->my_bp);

	return E_OK;
}

#endif


long slb_load(const char *sharedlib, const char *path, long ver, SLB_HANDLE *slb, SLB_EXEC *slbexec)
{
	long err;

	err = Slbopen(sharedlib, path, ver, slb, slbexec);
	if (err == ENOSYS || err == EPLFMT)
	{
#ifndef NO_LOCAL_SLB
		os_slb = 0;
		err = localSlbLoad(sharedlib, path, ver, slb, slbexec);
#endif
	} else if (err < 0)
	{
		const char *ptr;
		const char *slb_path;
		size_t l;
		size_t j;
		long err2;
		char file[256];

		slb_path = user_slbpath;

		if (slb_path != NULL)
		{
			while (slb_path[0])
			{
				ptr = strchr(slb_path, ';');
				if (!ptr)
					ptr = slb_path + strlen(slb_path);

				strncpy(file, slb_path, ptr - slb_path);
				file[ptr - slb_path] = 0;
				l = strlen(file);
				while (l && (file[l - 1] == ' ' || file[l - 1] == '\t'))
					file[--l] = 0;

				for (j = 0; j < l; j++)
					if (file[j] == '/')
						file[j] = '\\';
				if (file[l - 1] != '\\')
					strcat(file, "\\");

				err2 = Slbopen(sharedlib, file, ver, slb, slbexec);
				if (err2 > 0)
				{
					err = err2;
					break;
				}
				slb_path = ptr;
				while (*slb_path == ' ' || *slb_path == '\t' || *slb_path == ';')
					slb_path++;
			}
		}
	}

	if (err < 0)
	{
		*slb = 0;
		return err;
	}

	return 0;
}


long slb_unload(SLB_HANDLE slb)
{
	long err;

	if (os_slb)
		err = Slbclose(slb);
	else
		err = localSlbUnload(slb);

	if (err < 0)
		return err;

	return 0;
}


void slb_setpath(const char *slbpath)
{
	user_slbpath = slbpath;
}
