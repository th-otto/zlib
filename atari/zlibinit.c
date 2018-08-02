/*
 * zlibinit.c - initialization code for the shared library
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#define ZLIB_COMPILATION
#include "zlib.h"
#include <stdio.h>
#include <mint/basepage.h>
#include <mint/mintbind.h>
#include <mint/slb.h>
#include <errno.h>
#include "zlibstr.h"

#if defined(__MSHORT__) || defined(__PUREC__) || defined(__AHCC__)
# error "the zlib.slb must not be compiled with -mshort"
#endif

#ifndef NO_DUMMY_DECL
struct internal_state      {int dummy;}; /* for buggy compilers */
#endif



#define MINT_MAX_PID 999
#define MAX_PIDS (MINT_MAX_PID + 1)

struct per_proc {
	struct _zlibslb_funcs *funcs;
	pid_t pid;
};

static struct per_proc procs[MAX_PIDS];

static pid_t slb_user(void)
{
	pid_t pid = Pgetpid();
	if (pid == (pid_t)-ENOSYS)
		pid = 1;
	return pid;
}


static struct per_proc *get_proc(pid_t pid, pid_t slot)
{
	int i;
	
	/*
	 * see if we can use it as a direct index into our array
	 */
	if (pid > 0 && pid < MAX_PIDS && procs[pid].pid == slot)
		return &procs[pid];
	/*
	 * TODO: if MiNT ever uses pids >= 1000,
	 * use a hash instead
	 */
	for (i = 1; i < MAX_PIDS; i++)
		if (procs[i].pid == slot)
			return &procs[i];
	return NULL;
}


__attribute__((__noinline__))
struct _zlibslb_funcs *zlib_get_slb_funcs(void)
{
	pid_t pid = slb_user();
	struct per_proc *proc = get_proc(pid, pid);
	if (proc == NULL)
		return NULL;
	return proc->funcs;
}


/*
 * these are not optional and cannot be set
 * to zero in the header, even if they
 * currently don't do anything
 */
long zlib_init(void)
{
	return 0;
}


void zlib_exit(void)
{
}


long zlib_open(BASEPAGE *bp)
{
	pid_t pid = slb_user();
	struct per_proc *proc = get_proc(pid, 0);
	
	(void)(bp);
	if (proc == NULL)
		return -ENFILE; /* ENFILE: file table overflow, well, proc table in this case */
	/*
	 * check if SLB is already in use by this process;
	 * should not happen since MiNT should have taken care of that already
	 */
	if (proc->funcs != NULL)
		return -EACCES;
	
	proc->pid = pid;
	
	return 0;
}


void zlib_close(BASEPAGE *bp)
{
	pid_t pid = slb_user();
	struct per_proc *proc = get_proc(pid, pid);

	(void)(bp);
	if (proc == NULL)
		return;
	proc->funcs = NULL;
	proc->pid = 0;
}


/*
 * get the function table pointer passed from the application.
 * Automatically done in slb_zlib_open()
 */
__attribute__((__noinline__))
static long zlib_set_imports(struct _zlibslb_funcs *funcs)
{
	pid_t pid = slb_user();
	struct per_proc *proc = get_proc(pid, pid);

	if (proc == NULL)
		return -ESRCH;
	if (funcs->struct_size != sizeof(*funcs))
		return -EINVAL;
	if (funcs->zlib_vernum > ZLIB_VERNUM)
		return -EBADARG;
	if (funcs->int_size != sizeof(int))
		return -ERANGE;
	proc->funcs = funcs;
	return 0;
}


__attribute__((__noinline__))
static long slb_compile_flags(void)
{
	long flags = 0;
#if defined(__mc68020__) || defined(__mc68030__) || defined(__mc68040__) || defined(__mc68060__) || defined(__mc68080__) || defined(__apollo__)
    flags |= (1L << 16);
#endif
#if defined(__mcoldfire__)
    flags |= (1L << 17);
#endif
	return flags;
}


long _CDECL zlib_slb_control(long fn, void *arg)
{
	switch ((int)fn)
	{
	case 0:
		return slb_compile_flags();
	case 1:
		return zlib_set_imports(arg);
	}
	return -ENOSYS;
}


/*
 * just redefining memcpy is not enough;
 * the compiler will also generate references to it
 */
void *(memcpy)(void *dest, const void *src, size_t len)
{
	return memcpy(dest, src, len);
}


/* same for strlen */
size_t (strlen)(const char *str)
{
	return strlen(str);
}
