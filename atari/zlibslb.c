/*
 * zlibslb.c - minimalistic versions of some library functions
 *
 * Used only when compiling the shared library code,
 * to redirect standard library functions to the
 * library that was linked to the application
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#define ZLIB_COMPILATION
#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mint/osbind.h>
#include <mint/mintbind.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "zlib.h"
#include "zlibslb.h"

#undef errno
int errno;

#ifndef _REALO_NOATIME
#define _REALO_NOATIME    0x000004               /* Do not set atime.  */
#endif
#ifndef _REALO_APPEND
#define _REALO_APPEND     0x000008               /* this is what MiNT uses */
#endif
#ifndef _REALO_NOINHERIT
#define _REALO_NOINHERIT  0x000080                /* this is what MiNT uses */
#endif
#ifndef _REALO_NDELAY
#define _REALO_NDELAY     0x000100               /* this is what MiNT uses */
#endif
#ifndef _REALO_CREAT
#define _REALO_CREAT      0x000200               /* create new file if needed */
#endif
#ifndef _REALO_TRUNC
#define _REALO_TRUNC      0x000400               /* make file 0 length */
#endif
#ifndef _REALO_EXCL
#define _REALO_EXCL       0x000800               /* error if file exists */
#endif
#ifndef _REALO_DIRECTORY
#define _REALO_DIRECTORY  0x010000UL
#endif
#ifndef _REALO_SYNC
#define _REALO_SYNC       0x000000       /* sync after writes (NYI) */
#endif
#ifndef O_NOATIME
#define O_NOATIME       _REALO_NOATIME
#endif
#define __O_NOINHERIT   _REALO_NOINHERIT
#undef _REALO_SHMODE
#define _REALO_SHMODE(mode) (((mode) & (O_SHMODE)) >> 4)
#ifndef __O_DIRECTORY
#define __O_DIRECTORY   0x010000UL
#endif
#ifndef __O_NOFOLLOW
#define __O_NOFOLLOW    0x020000UL
#endif
#ifndef __O_CLOEXEC
#define __O_CLOEXEC     0x100000UL
#endif
#ifndef FTRUNCATE
#define FTRUNCATE (('F'<< 8) | 4)
#endif


#undef __set_errno
static void __set_errno(int e)
{
	errno = e;
}



/*
 * from our flags, calculate the mode that
 * has to be passed to the OS
 */
static long __real_omode(long iomode)
{
	long realmode;						/* which bits get passed to the OS? */

	/* these are always identical */
	realmode = iomode & O_ACCMODE;

	/* now translate some emulated flags */
	if (iomode & O_SYNC)
		realmode |= _REALO_SYNC;
	if (iomode & O_NDELAY)
		realmode |= _REALO_NDELAY;
	if (iomode & O_TRUNC)
		realmode |= _REALO_TRUNC;
	if (iomode & O_CREAT)
		realmode |= _REALO_CREAT;
	if (iomode & O_APPEND)
		realmode |= _REALO_APPEND;
	if (iomode & O_EXCL)
		realmode |= _REALO_EXCL;
	
	if ((iomode & O_SHMODE) == O_COMPAT)
		realmode |= _REALO_SHMODE(O_DENYNONE);
	else
		realmode |= _REALO_SHMODE(iomode);

	if (iomode & O_NOATIME)
		realmode |= _REALO_NOATIME;
	if (iomode & __O_DIRECTORY)
		realmode |= _REALO_DIRECTORY;
	if (iomode & __O_NOINHERIT)
		realmode |= _REALO_NOINHERIT;
	
	return realmode;
}



int stat(const char *path, struct stat *buff)
{
	_DTA dta;
    _DTA *old_dta = Fgetdta();
    long ret;

    Fsetdta(&dta);

    ret = Fsfirst(path, FA_DIR | FA_RDONLY | FA_HIDDEN | FA_SYSTEM);
    if (ret == 0)
    {
        buff->st_dev = 0;
        buff->st_ino = 0;
        buff->st_mode = dta.dta_attribute;
        buff->st_nlink = 0;
        buff->st_uid = 0;
        buff->st_gid = 0;
        buff->st_rdev = 0;
        buff->st_size = dta.dta_size;
        buff->st_atime = dta.dta_time;
        buff->st_mtime = dta.dta_time;
        buff->st_ctime = dta.dta_time;
    }

	Fsetdta(old_dta);

    return ret;
}


static int _open_v(const char *_filename, int iomode, va_list argp)
{
	long rv;
	long realmode;						/* which bits get passed to the OS? */
	long fcbuf;							/* a temporary buffer for Fcntl */
	struct stat sb;
	unsigned int pmode = 0;
	const char *filename = _filename;

	if (!_filename)
	{
		__set_errno(EFAULT);
		return -1;
	}

	if (*_filename == '\0')
	{
		__set_errno(ENOENT);
		return -1;
	}

	if (iomode & O_CREAT)
		pmode = va_arg(argp, unsigned int);

	/* set the file access modes correctly */
	realmode = __real_omode(iomode);

	rv = -ENOSYS;
	if (iomode & __O_NOFOLLOW)
		rv = Fstat64(1, filename, &sb);
	if (rv == -ENOSYS)
	{
		rv = stat(filename, &sb);
		if (rv != 0)
			rv = -errno;
	}

	if (rv == 0)						/* file exists */
	{
		if (S_ISLNK(sb.st_mode) && (iomode & __O_NOFOLLOW))
		{
			__set_errno(ELOOP);
			return -1;
		}

		if (S_ISDIR(sb.st_mode))
		{
			__set_errno(EISDIR);
		} else
		{
			if (iomode & __O_DIRECTORY)
			{
				__set_errno(ENOTDIR);
				return -1;
			}
		}

		if ((iomode & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
		{
			__set_errno(EEXIST);
			return -1;
		}

		rv = Fopen(filename, realmode & ~_REALO_CREAT);
		if (rv == -ENOENT)
			/* race: file can disappear between stat and open... */
			goto noent;
		if ((iomode & O_TRUNC) && (rv >= 0))
		{
			/* Give up if the mode flags conflict */
			if ((iomode & O_ACCMODE) == O_RDONLY)
			{
				(void) Fclose((int) rv);
				__set_errno(EACCES);
				return -1;
			}
			/* Try the FTRUNCATE first.  If it fails, have GEMDOS
			   truncate it, then reopen with the correct modes.
			 */
			fcbuf = 0L;
			if (Fcntl((int) rv, (long) &fcbuf, FTRUNCATE) < 0)
			{
				(void) Fclose((int) rv);
				rv = Fcreate(filename, 0x00);
				if (rv < 0)
				{
					__set_errno(-rv);
					return -1;
				}
				(void) Fclose((int) rv);
				rv = Fopen(filename, realmode);
			}
		}
	} else								/* file doesn't exist */
	{
	  noent:
		if (iomode & O_CREAT)
		{
			/* posix requirement for trailing slash check */
			size_t len = strlen(filename);

			if (len > 0 && (filename[len - 1] == '/' || filename[len - 1] == '\\'))
			{
				__set_errno(EISDIR);
				return -1;
			}

			rv = Fopen(filename, realmode);
			if (rv == -ENOENT)
				rv = Fcreate(filename, 0x00);
			if (rv >= 0)
			{
				if (Ffchmod(rv, pmode) == -ENOSYS)
					(void) Fchmod(filename, pmode);
			}
		}
	}

	if (rv < 0)
	{
		__set_errno(-rv);
		return -1;
	}

	if (iomode & __O_CLOEXEC)
	{
		/* set the close-on-exec flag */
		fcbuf = Fcntl((int) rv, 0, F_GETFD);
		if ((fcbuf >= 0) && !(fcbuf & FD_CLOEXEC))
			(void) Fcntl((int) rv, fcbuf | FD_CLOEXEC, F_SETFD);
	}
	
	if (iomode & O_APPEND)
		(void) Fseek(0L, (int) rv, SEEK_END);

	return (int) rv;
}


static int my_open(const char *filename, int access, ...)
{
    va_list args;
    int retval;

    va_start(args, access);
    retval = _open_v(filename, access, args);

    return retval;
}


static int my_close(int fd)
{
    long ret;

    ret = Fclose(fd);

    if (ret < 0)
    {
        __set_errno(-ret);
        return -1;
    }
    return 0;
}


static ssize_t my_read(int fd, void *buf, size_t nbytes)
{
    long result;

    result = Fread(fd, nbytes, buf);

    if (result < 0)
    {
        __set_errno(-result);
        return -1;
    }
    return result;
}


static ssize_t my_write(int fd, const void *buf, size_t nbytes)
{
    long result;

    result = Fwrite(fd, nbytes, buf);

    if (result < 0)
    {
        __set_errno(-result);
        return -1;
    }
    return result;
}


static off_t my_lseek(int fd, off_t offset, int whence)
{
	return Fseek(offset, fd, whence);
}


#define  A	  16807L					/*  A "good" multiplier   */
#define  M   2147483647L				/*  Modulus: 2^31 - 1     */
#define  Q       127773L				/*  M / A         */
#define  R         2836L				/*  M % A         */


static long _lseed = 1L;


static void my_srand(unsigned int seed)
{
	_lseed = seed;
}


static int my_rand(void)
{
	_lseed = A * (_lseed % Q) - R * (_lseed / Q);

	if (_lseed < 0)
		_lseed += M;

	return ((int) (_lseed & RAND_MAX));	/* how "good" is it now ? */
}


/*
 * stdio functions
 */
FILE *__stdio_head;
#define FILE_SET_HANDLE(fp, H) (fp)->__cookie = ((void*)(long)(H))
#define FILE_GET_HANDLE(fp) ((long)(fp)->__cookie)


static FILE *my_fopen(const char *path, const char *mode)
{
	FILE *fp;
	long fd;
	int create = 0;
	int append = 0;
	int readmode = 0;
	int writemode = 0;
	int i;

	if (mode == NULL)
	{
		__set_errno(EFAULT);
		return NULL;
	}

	switch (*mode)
	{
	case 'a':
		writemode = create = append = 1;
		break;
	case 'w':
		writemode = create = 1;
		break;
	case 'r':
		readmode = 1;
		break;
	default:
		return NULL;
	}

	for (i = 1; i < 4; ++i)
	{
		switch (*++mode)
		{
		case '\0':
			break;
		case '+':
			readmode = writemode = 1;
			continue;
		case 'b':
			/* ignore binary */ ;
			continue;
		case 'x':
			/* ignore exclusive */ ;
			continue;
		}
		break;
	}

	if ((fp = malloc(sizeof(FILE))) != NULL)
	{
		if (append)
		{
			fd = Fopen(path, writemode ? 1 + readmode : 0);
			if (fd >= 0)
			{
				Fseek(0, fd, SEEK_END);
				goto ok;
			}
		}
		if (create)
		{
			fd = Fcreate(path, 0);
			if (fd < 0)
			{
				free(fp);
				__set_errno(-fd);
				return NULL;
			}
			if (readmode)
				goto ok;
			Fclose(fd);
		}
		if ((fd = Fopen(path, writemode ? 1 + readmode : 0)) >= 0)
			goto ok;
		__set_errno(-fd);
		free(fp);
	}
	return NULL;
ok:
	fp->__magic = _IOMAGIC;
	FILE_SET_HANDLE(fp, fd);
	fp->__next = __stdio_head;
	__stdio_head = fp;
	return fp;
}


static int my_fclose(FILE *fp)
{
	if (fp && fp->__magic == _IOMAGIC)
	{
		FILE **prev;
		
		Fclose(FILE_GET_HANDLE(fp));
		FILE_SET_HANDLE(fp, -7);
		fp->__magic = 0;

		prev = &__stdio_head;
		for (prev = &__stdio_head; (*prev) && *prev != fp; prev = &(*prev)->__next)
			;
		if (*prev == fp)
		{
			*prev = fp->__next;
			free(fp);
		}
	}
	return 0;
}


static int my_fseek(FILE *fp, long offset, int origin)
{
	long res;

	if (fp == NULL || fp->__magic != _IOMAGIC)
	{
		__set_errno(EBADF);
		return -1;
	}
	res = Fseek(offset, FILE_GET_HANDLE(fp), origin);
	if (res < 0)
	{
		__set_errno(-res);
		return -1;
	}
	fp->__eof = 0;
	fp->__pushed_back = 0;
	return 0;
}


static long my_ftell(FILE *stream)
{
	return Fseek(0, FILE_GET_HANDLE(stream), SEEK_CUR);
}


static size_t my_fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t bytes = size * nmemb;
	long rc = Fread(FILE_GET_HANDLE(stream), bytes, ptr);

	if (rc < 0)
	{
		stream->__error = 1;
		__set_errno(-rc);
		rc = 0;
	} else
	{
		if (rc < bytes)
			stream->__eof = 1;
		rc /= size;
	}
	return rc;
}


static size_t my_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	long rc = Fwrite(FILE_GET_HANDLE(stream), size * nmemb, ptr);
	if (rc < 0)
	{
		stream->__error = 1;
		__set_errno(-rc);
		rc = 0;
	} else
	{
		rc /= size;;
	}
	return rc;
}


static int my_ferror(FILE *stream)
{
	return stream->__error;
}


#if DEBUG

struct _mem_stream { char *xstring; char *xestring; };

static int __addchar(int c, void *_stream)
{
	struct _mem_stream *stream = (struct _mem_stream *)_stream;

	if (stream->xstring >= stream->xestring)
		stream->xstring++;
	else
		*stream->xstring++ = (char) c;

	return 1;
}

#define ONLY_INTEGER_IO

#undef isdigit
#define isdigit(c)	((unsigned char)(c) >= '0' && (unsigned char)(c) <= '9')
#undef isupper
#define isupper(c)	((unsigned char)(c) >= 'A' && (unsigned char)(c) <= 'Z')
#undef islower
#define islower(c)	((unsigned char)(c) >= 'a' && (unsigned char)(c) <= 'z')
#undef isalpha
#define isalpha(c)	(isupper((c)) || islower(c))
#undef tolower
#define tolower(c)	(isupper(c) ? ((c) + 'a' - 'A') : (c))
#undef toupper
#define toupper(c)	(islower(c) ? ((c) - 'a' - 'A') : (c))

#undef isspace
#define isspace(c)  (((c) == ' ') || ((c) == '\t') || ((c == '\n')) || ((c) == '\r') || ((c) == '\v'))


int atoi(const char *c)
{
    int value = 0;
    int negative = 0;

    while (isspace(*c)) c++;

    if (*c == '+')
    {
        c++;
    }
    else if (*c == '-')
    {
        negative = 1;
        c++;
    }

    while (isdigit(*c))
    {
        value *= 10;
        value += (int) (*c - '0');
        c++;
    }

    if (negative)
    {
        value=-value;
    }

    return value;
}


/*
 * Lexical definitions.
 *
 * All lexical space is allocated dynamically.
 * The eighth/sixteenth bit of characters is used to prevent recognition,
 * and eventually stripped.
 */
#define	META		0200
#define	ASCII		0177
#define	QUOTE		((char)	0200)		/* Eighth char bit used for 'ing */
#define	TRIM		0177				/* Mask to strip quote bit */
#define	UNDER		0000000				/* No extra bits to do both */
#define	BOLD		0000000				/* Bold flag */
#define	STANDOUT	META				/* Standout flag */
#define	LITERAL		0000000				/* Literal character flag */
#define	ATTRIBUTES	0200				/* The bits used for attributes */
#define	CHAR		0000177				/* Mask to mask out the character */

#define INF	32766						/* should be bigger than any field to print */

static char snil[] = "(nil)";

#ifdef ONLY_INTEGER_IO
static char const sfloat[] = ")taolf(";
#endif
static int __attribute__((noinline)) doprnt(int (*addchar) (int, void *), void *stream, const char *sfmt, va_list ap)
{
	char buf[128];
	char *bp;
	const char *f;

#ifndef ONLY_INTEGER_IO
	long double flt;
#endif
	long l;
	unsigned long u;
#ifdef STDIO_WITH_LONG_LONG
	long long ll;
	unsigned long long ull;
#endif
	int i;
	int fmt;
	int num = 0;
	int attributes = 0;

	f = sfmt;
	for (; *f; f++)
	{
		if (*f != '%')
		{
			/* then just out the char */
			num += (*addchar) ((int) (((unsigned char) *f) | attributes), stream);
		} else
		{
			unsigned char pad = ' ';
			const char *numbers;
			int flush_left = 0;
			int f_width = 0;
			int prec = INF;
			int hash = 0;
			int do_long = 0;
			int sign = 0;

			f++;						/* skip the % */

			if (*f == '-')
			{							/* minus: flush left */
				flush_left = 1;
				f++;
			}

			if (*f == '0')
			{
				/* padding with 0 rather than blank */
				pad = '0';
				f++;
			}
			if (*f == '*')
			{
				/* field width */
				f_width = va_arg(ap, int);

				f++;
			} else if (isdigit((unsigned char) *f))
			{
				f_width = atoi(f);
				while (isdigit((unsigned char) *f))
					f++;				/* skip the digits */
			}

			if (*f == '.')
			{							/* precision */
				f++;
				if (*f == '*')
				{
					prec = va_arg(ap, int);

					f++;
				} else if (isdigit((unsigned char) *f))
				{
					prec = atoi(f);
					while (isdigit((unsigned char) *f))
						f++;			/* skip the digits */
				}
			}

			if (*f == '#')
			{							/* alternate form */
				hash = 1;
				f++;
			}

			if (*f == 'l')
			{							/* long format */
				do_long++;
				f++;
				if (*f == 'l')
				{
					do_long++;
					f++;
				}
			} else if (*f == 'L')
			{
				do_long = 1;
				f++;
			} else if (*f == 'z')
			{
				do_long = sizeof(size_t) > sizeof(int);
				f++;
			}

			fmt = (unsigned char) *f;
			if (fmt != 'S' && fmt != 'Q' && fmt != 'X' && isupper(fmt))
			{
				do_long = 1;
				fmt = tolower(fmt);
			}
			bp = buf;
			switch (fmt)
			{							/* do the format */
			case 'i':
			case 'd':
				switch (do_long)
				{
				case 0:
					l = (long) (va_arg(ap, int));

					break;
#ifdef STDIO_WITH_LONG_LONG
				case 2:
					ll = va_arg(ap, long long);

					if (ll > LONG_MAX || ll < LONG_MIN)
					{					/* use 64 bit arithmetic only if needed */
						if (ll < 0)
						{
							sign = 1;
							ll = -ll;
						}
						do
						{
							*bp++ = (char) (ll % 10) + '0';
						} while ((ll /= 10) > 0);
						l = 0;
					} else
						l = (long) ll;
					break;
#endif
				case 1:
				default:
					l = va_arg(ap, long);

					break;
				}
				if (bp == buf)
				{
					if (l < 0)
					{
						sign = 1;
						l = -l;
					}
					do
					{
						*bp++ = (char) (l % 10) + '0';
					} while ((l /= 10) > 0);
				}
				if (sign)
					*bp++ = '-';
				f_width = f_width - (int) (bp - buf);
				if (!flush_left)
					while (f_width-- > 0)
						num += (*addchar) ((int) (pad | attributes), stream);
				for (bp--; bp >= buf; bp--)
					num += (*addchar) ((int) (((unsigned char) *bp) | attributes), stream);
				if (flush_left)
					while (f_width-- > 0)
						(*addchar) ((int) (' ' | attributes), stream);
				break;

			case 'f':
			case 'e':
			case 'g':
#ifdef ONLY_INTEGER_IO
				{
					const char *p = sfloat;

					while (*p)
						*bp++ = *p++;
					pad = ' ';
					if (do_long)
						(va_arg(ap, long double));
					else
						(va_arg(ap, double));
#else
				/* this is actually more than stupid, but does work for now */
				if (do_long)
					flt = va_arg(ap, long double);
				else
					flt = va_arg(ap, double);	/* beware: va_arg() extends float to double! */

				if (flt < 0)
				{
					sign = 1;
					flt = -flt;
				}
				{
					int quotient, remainder;

					quotient = (int) flt;
					remainder = (flt - quotient) * 10E5;

					for (i = 0; i < 6; i++)
					{
						*bp++ = (char) (remainder % 10) + '0';
						remainder /= 10;
					}
					*bp++ = '.';
					do
					{
						*bp++ = (char) (quotient % 10) + '0';
					} while ((quotient /= 10) > 0);
					if (sign)
						*bp++ = '-';
#endif
					f_width = f_width - (int) (bp - buf);
					if (!flush_left)
						while (f_width-- > 0)
							num += (*addchar) ((int) (pad | attributes), stream);
					for (bp--; bp >= buf; bp--)
						num += (*addchar) ((int) (((unsigned char) *bp) | attributes), stream);
					if (flush_left)
						while (f_width-- > 0)
							(*addchar) ((int) (' ' | attributes), stream);
				}
				break;

			case 'p':
				do_long = 1;
				hash = 1;
				fmt = 'x';
				/* no break */
			case 'o':
			case 'x':
			case 'X':
			case 'u':
				numbers = "0123456789abcdef";
				switch (do_long)
				{
				case 0:
					u = (unsigned long) (va_arg(ap, unsigned int));

					break;
#ifdef STDIO_WITH_LONG_LONG
				case 2:
					ull = va_arg(ap, unsigned long long);

					if (ull > ULONG_MAX)
					{					/* use 64 bit arithmetic only if needed */
						switch (fmt)
						{
						case 'u':
						default:
							do
							{
								*bp++ = numbers[ull % 10];
							} while ((ull /= 10) > 0);
							break;
						case 'o':
							do
							{
								*bp++ = numbers[ull % 8];
							} while ((ull /= 8) > 0);
							break;
						case 'X':
							numbers = "0123456789ABCDEF";
						case 'x':
							do
							{
								*bp++ = numbers[ull % 16];
							} while ((ull /= 16) > 0);
							break;
						}
					} else
						u = (unsigned long) ull;
					break;
#endif
				case 1:
				default:
					u = va_arg(ap, unsigned long);

					break;
				}
				if (bp == buf)
				{
					switch (fmt)
					{
					case 'u':
					default:
						do
						{
							*bp++ = numbers[u % 10];
						} while ((u /= 10) > 0);
						break;
					case 'o':
						do
						{
							*bp++ = numbers[u % 8];
						} while ((u /= 8) > 0);
						break;
					case 'X':
						numbers = "0123456789ABCDEF";
					case 'x':
						do
						{
							*bp++ = numbers[u % 16];
						} while ((u /= 16) > 0);
						break;
					}
				}
				if (hash)
				{
					switch (fmt)
					{
					case 'X':
					case 'x':
						*bp++ = 'x';
					case 'o':
						*bp++ = '0';
					}
				}
				i = f_width - (int) (bp - buf);
				if (!flush_left)
					while (i-- > 0)
						num += (*addchar) ((int) (pad | attributes), stream);
				for (bp--; bp >= buf; bp--)
					num += (*addchar) ((int) (((unsigned char) *bp) | attributes), stream);
				if (flush_left)
					while (i-- > 0)
						num += (*addchar) ((int) (' ' | attributes), stream);
				break;

			case 'c':
				i = va_arg(ap, int);
				num += (*addchar) ((int) (i | attributes), stream);
				break;

			case 'S':
			case 'Q':
			case 's':
			case 'q':
				bp = va_arg(ap, char *);

				if (!bp)
					bp = snil;
				f_width = f_width - strlen((char *) bp);
				if (!flush_left)
					while (f_width-- > 0)
						num += (*addchar) ((int) (pad | attributes), stream);
				for (i = 0; *bp && i < prec; i++)
				{
					if (fmt == 'q' && (*bp & QUOTE))
						num += (*addchar) ((int) ('\\' | attributes), stream);
					num += (*addchar) ((int) (((unsigned char) *bp & TRIM) | attributes), stream);
					bp++;
				}
				if (flush_left)
					while (f_width-- > 0)
						num += (*addchar) ((int) (' ' | attributes), stream);
				break;

			case 'a':
				attributes = va_arg(ap, int);
				break;

			case '%':
				num += (*addchar) ((int) ('%' | attributes), stream);
				break;

			default:
				break;
			}
			flush_left = 0, f_width = 0, prec = INF, hash = 0, do_long = 0;
			sign = 0;
			pad = ' ';
		}
	}
	return num;
}


int __attribute__((noinline)) vsnprintf(char *str, size_t size, const char *fmt, va_list va)
{
	struct _mem_stream stream;
	stream.xstring = str;
	stream.xestring = str + size - 1;
	doprnt(__addchar, &stream, fmt, va);
	if (stream.xstring <= stream.xestring)
		*stream.xstring = '\0';
	else
		*stream.xestring = '\0';

	return stream.xstring - str;
}

#pragma GCC optimize "-fomit-frame-pointer"
#pragma GCC diagnostic ignored "-Wclobbered"

#define ASM_NATFEAT3(opcode) "\t.word " #opcode "\n"
#define ASM_NATFEAT2(opcode) ASM_NATFEAT3(opcode)
#define ASM_NATFEAT(n) ASM_NATFEAT2(n)

#define NATFEAT_ID   0x7300
#define NATFEAT_CALL 0x7301

static long __attribute__((noinline)) __CDECL _nf_get_id(const char *feature_name)
{
	register long ret __asm__ ("d0");
	__asm__ volatile(
		ASM_NATFEAT(NATFEAT_ID)
	: "=g"(ret)  /* outputs */
	: "m"(feature_name) /* inputs  */
	: __CLOBBER_RETURN("d0") "d1", "cc" AND_MEMORY /* clobbered regs */
	);
	return ret;
}
#define NF_ID_STDERR    "NF_STDERR"

long __CDECL (*p_nf_get_id)(const char *feature_name) = _nf_get_id;


static long __attribute__((noinline)) __CDECL _nf_call(long id, ...)
{
	register long ret __asm__ ("d0");
	__asm__ volatile(
		ASM_NATFEAT(NATFEAT_CALL)
	: "=g"(ret)  /* outputs */
	: "m"(id) /* inputs  */
	: __CLOBBER_RETURN("d0") "d1", "cc" AND_MEMORY /* clobbered regs */
	);
	return ret;
}
long __CDECL (*p_nf_call)(long id, ...) = _nf_call;

static long nfid_stderr;

static int nf_debugvprintf(const char *format, va_list args)
{
	char buf[512];

	if (nfid_stderr == 0)
	{
		nfid_stderr = p_nf_get_id(NF_ID_STDERR);
	}
		
	vsnprintf(buf, sizeof(buf), format, args);
	return (int)p_nf_call(nfid_stderr | 0, (unsigned long)buf);
}

void nf_debugprintf(const char *format, ...)
{
	va_list args;
	
	va_start(args, format);
	nf_debugvprintf(format, args);
	va_end(args);
}


#endif /* DEBUG */


static z_int_t __CDECL my_get_errno(void)
{
	return errno;
}


void init_minilib(struct _zlibslb_funcs *funcs)
{
	if (funcs->p_get_errno == 0)
		funcs->p_get_errno = my_get_errno;
	if (funcs->p_open == 0)
		funcs->p_open = my_open;
	if (funcs->p_close == 0)
		funcs->p_close = my_close;
	if (funcs->p_read == 0)
		funcs->p_read = my_read;
	if (funcs->p_write == 0)
		funcs->p_write = my_write;
	if (funcs->p_lseek == 0)
		funcs->p_lseek = my_lseek;
	if (funcs->p_fopen == 0)
		funcs->p_fopen = my_fopen;
	if (funcs->p_fclose == 0)
		funcs->p_fclose = my_fclose;
	if (funcs->p_fseek == 0)
		funcs->p_fseek = my_fseek;
	if (funcs->p_fseeko == 0)
		funcs->p_fseeko = (z_int_t __CDECL (*)(FILE *, __off_t, z_int_t))my_fseek;
	if (funcs->p_ftell == 0)
		funcs->p_ftell = my_ftell;
	if (funcs->p_ftello == 0)
		funcs->p_ftello = (off_t __CDECL (*)(FILE *))my_ftell;
	if (funcs->p_fread == 0)
		funcs->p_fread = my_fread;
	if (funcs->p_fwrite == 0)
		funcs->p_fwrite = my_fwrite;
	if (funcs->p_ferror == 0)
		funcs->p_ferror = my_ferror;
	if (funcs->p_rand == 0)
		funcs->p_rand = my_rand;
	if (funcs->p_srand == 0)
		funcs->p_srand = my_srand;
}
