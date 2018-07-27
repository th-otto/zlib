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
#include "zlibstruct.h"

#ifdef __MSHORT__
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


static struct per_proc *get_proc(pid_t pid, pid_t slot)
{
	int i;
	
	/*
	 * see if we can use it as a direct index into our array
	 */
	if (pid >= 0 && pid < MAX_PIDS)
		return &procs[pid];
	/*
	 * TODO: if MiNT ever uses pids >= 1000,
	 * use a hash instead
	 */
	for (i = 0; i < MAX_PIDS; i++)
		if (procs[i].pid == slot)
			return &procs[i];
	return NULL;
}


struct _zlibslb_funcs *zlib_get_slb_funcs(void)
{
	pid_t pid = Pgetpid();
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
	pid_t pid = Pgetpid();
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
	pid_t pid = Pgetpid();
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
long zlib_set_imports(struct _zlibslb_funcs *funcs)
{
	pid_t pid = Pgetpid();
	struct per_proc *proc = get_proc(pid, pid);

	if (proc == NULL)
		return -ESRCH;
	if (funcs->struct_size != sizeof(*funcs))
		return -EBADARG;
	if (funcs->zlib_vernum > ZLIB_VERNUM)
		return -EBADARG;
	if (funcs->int_size != sizeof(int))
		return -EBADARG;
	proc->funcs = funcs;
	return 0;
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
