/* miniinflate.c -- simulate gzip using the zlib compression library
 * Copyright (C) 1995-2006, 2010, 2011, 2016 Jean-loup Gailly
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/*
 * inflate is a minimal implementation of the gzip utility. This is
 * only an example of using zlib and isn't meant to replace the
 * full-featured gzip. No attempt is made to deal with file systems
 * limiting names to 14 or 8+3 characters, etc... Error checking is
 * very limited. So use inflate only for testing; use gzip for the
 * real thing. On MSDOS, use only on file names without extension
 * or in pipe mode.
 */

#include "../zlib.h"
#include "zutil.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#ifdef USE_MMAP
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#endif

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#include <fcntl.h>
#include <io.h>
#ifdef UNDER_CE
#include <stdlib.h>
#endif
#define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#define SET_BINARY_MODE(file)
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf _snprintf
#endif

#ifdef VMS
#define unlink delete
#define GZ_SUFFIX "-gz"
#endif
#ifdef RISCOS
#define unlink remove
#define GZ_SUFFIX "-gz"
#define fileno(file) file->__file
#endif
#if defined(__MWERKS__) && __dest_os != __be_os && __dest_os != __win32_os
#include <unix.h>						/* for fileno */
#endif

#if !defined(Z_HAVE_UNISTD_H) && !defined(_LARGEFILE64_SOURCE)
#ifndef WIN32							/* unlink already in stdio.h for WIN32 */
extern int unlink(const char *);
#endif
#endif


/*
 * gzip header:
 *    magic 0x1f 0x8b
 *    cm    0x08
 *    flg   0x00
 *    mtime 0x00 0x00 0x00 0x00
 *    xfl   0x02
 *    os    0x03
 * 
 *
 * deflate stream header:
 *   CMF FLG
 *
 *   CMF: compression method and flags
 *        0..3: CM compression method (8)
 *        4..7: CINFO compression info (ln2 window-size, minus 8)
 *              eg. value of 7 = 1 << 15 = 32k windows size
 *
 *   FLG: Flags
 *        0..4 FCHECK check bits for CMF and FLG
 *             (CMF*256 + FLG) must be multiple of 31
 *        5    FDICT preset dictionary
 *             if set, a DICTID identifier follows
 *        6..7 Compression level (informative only)
 */

#if defined(UNDER_CE)
#include <windows.h>
#define perror(s) pwinerror(s)

/* Map the Windows error number in ERROR to a locale-dependent error
   message string and return a pointer to it.  Typically, the values
   for ERROR come from GetLastError.

   The string pointed to shall not be modified by the application,
   but may be overwritten by a subsequent call to strwinerror

   The strwinerror function does not change the current setting
   of GetLastError.  */

static char *strwinerror(DWORD error)
{
	static char buf[1024];

	wchar_t *msgbuf;
	DWORD chars = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
								NULL,
								error,
								0,		/* Default language */
								(LPVOID) & msgbuf,
								0,
								NULL);

	if (chars != 0)
	{
		/* If there is an \r\n appended, zap it.  */
		if (chars >= 2 && msgbuf[chars - 2] == '\r' && msgbuf[chars - 1] == '\n')
		{
			chars -= 2;
			msgbuf[chars] = 0;
		}

		if (chars > sizeof(buf) - 1)
		{
			chars = sizeof(buf) - 1;
			msgbuf[chars] = 0;
		}

		wcstombs(buf, msgbuf, chars + 1);
		LocalFree(msgbuf);
	} else
	{
		sprintf(buf, "unknown win32 error (%ld)", error);
	}

	return buf;
}

static void pwinerror(const char *s)
{
	DWORD error = GetLastError();
	if (s && *s)
		fprintf(stderr, "%s: ", s);
	fprintf(stderr, "%s\n", strwinerror(error));
	SetLastError(error);
}

#endif /* UNDER_CE */

#ifndef GZ_SUFFIX
#define GZ_SUFFIX ".gz"
#endif
#define SUFFIX_LEN (sizeof(GZ_SUFFIX)-1)

#define BUFLEN      16384
#define MAX_NAME_LEN 1024

#undef local
#ifdef MAXSEG_64K
#define local static
   /* Needed for systems with limitation on stack size. */
#else
#define local
#endif

#include <unistd.h>						/* for unlink() */

static char *prog;

/* ===========================================================================
 * Display error message and exit
 */
static void error(const char *msg, const char *msg2)
{
	fprintf(stderr, "%s: ", prog);
	if (msg2)
		fprintf(stderr, "%s: ", msg2);
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

static void *myalloc(void *q, unsigned int n, unsigned int m)
{
	(void) q;
	return z_calloc(n, m);
}

static void myfree(void *q, void *p)
{
	(void) q;
	z_free(p);
}

#define gzFile my_gzFile
#define gzopen my_gzopen
#define gzdopen my_gzdopen
#define gz_open my_gz_open
#define gzwrite my_gzwrite
#define gzread my_gzread
#define gzclose my_gzclose
#define gzerror my_gzerror

typedef struct mygzFile_s
{
	FILE *file;
	int write;
	int err;
	const char *msg;
	z_stream strm;
} *gzFile;

gzFile gzopen(const char *, const char *);
gzFile gzdopen(int, const char *);
int gzwrite(gzFile, const void *, unsigned);
int gzread(gzFile, void *, unsigned);
int gzclose(gzFile);
const char *gzerror(gzFile, int *);


static gzFile gz_open(const char *path, int fd, const char *mode)
{
	gzFile gz;
	int ret;
	int windowBits;

	gz = z_malloc(sizeof(*gz));
	if (gz == NULL)
		return NULL;
	gz->write = strchr(mode, 'w') != NULL;
	gz->strm.zalloc = myalloc;
	gz->strm.zfree = myfree;
	gz->strm.opaque = Z_NULL;
	windowBits = 15;
	if (strchr(mode, 'q') != NULL)
		windowBits = -windowBits;
	else if (strchr(mode, 'z') == NULL)
		windowBits |= 16;
	if (gz->write)
	{
		ret = deflateInit2(&(gz->strm), -1, 8, windowBits, 8, 0);
	} else
	{
		gz->strm.next_in = 0;
		gz->strm.avail_in = Z_NULL;
		ret = inflateInit2(&(gz->strm), windowBits);
	}
	if (ret != Z_OK)
	{
		z_free(gz);
		return NULL;
	}
	gz->file = path == NULL ? fdopen(fd, gz->write ? "wb" : "rb") : fopen(path, gz->write ? "wb" : "rb");
	if (gz->file == NULL)
	{
		gz->write ? deflateEnd(&(gz->strm)) : inflateEnd(&(gz->strm));
		z_free(gz);
		return NULL;
	}
	gz->err = Z_OK;
	gz->msg = "";
	return gz;
}


gzFile gzopen(const char *path, const char *mode)
{
	return gz_open(path, -1, mode);
}

gzFile gzdopen(int fd, const char *mode)
{
	return gz_open(NULL, fd, mode);
}

int gzwrite(gzFile gz, const void *buf, unsigned int len)
{
	z_stream *strm;
	unsigned char out[BUFLEN];

	if (gz == NULL || !gz->write)
		return 0;
	strm = &(gz->strm);
	strm->next_in = (void *) buf;
	strm->avail_in = len;
	do
	{
		strm->next_out = out;
		strm->avail_out = BUFLEN;
		(void) deflate(strm, Z_NO_FLUSH);
		fwrite(out, 1, BUFLEN - strm->avail_out, gz->file);
	} while (strm->avail_out == 0);
	return len;
}


int gzread(gzFile gz, void *buf, unsigned int len)
{
	int ret;
	unsigned got;
	unsigned char in[1];
	z_stream *strm;

	if (gz == NULL || gz->write)
		return 0;
	if (gz->err != Z_OK)
		return 0;
	strm = &(gz->strm);
	strm->next_out = (void *) buf;
	strm->avail_out = len;
	do
	{
		got = fread(in, 1, 1, gz->file);
		if (got == 0)
			break;
		strm->next_in = in;
		strm->avail_in = 1;
		ret = inflate(strm, Z_NO_FLUSH);
		if (ret == Z_DATA_ERROR)
		{
			error(strm->msg, zError(ret));
			gz->err = Z_DATA_ERROR;
			gz->msg = strm->msg;
			return 0;
		}
		if (ret == Z_STREAM_END)
			inflateReset(strm);
	} while (strm->avail_out);
	return len - strm->avail_out;
}


int gzclose(gzFile gz)
{
	z_stream *strm;
	unsigned char out[BUFLEN];

	if (gz == NULL)
		return Z_STREAM_ERROR;
	strm = &(gz->strm);
	if (gz->write)
	{
		strm->next_in = Z_NULL;
		strm->avail_in = 0;
		do
		{
			strm->next_out = out;
			strm->avail_out = BUFLEN;
			(void) deflate(strm, Z_FINISH);
			fwrite(out, 1, BUFLEN - strm->avail_out, gz->file);
		} while (strm->avail_out == 0);
		deflateEnd(strm);
	} else
	{
		inflateEnd(strm);
	}
	fclose(gz->file);
	z_free(gz);
	return Z_OK;
}


const char *gzerror(gzFile gz, int *err)
{
	*err = gz->err;
	return gz->msg;
}



/* ===========================================================================
 * Compress input to output then close both files.
 */

static void gz_compress(FILE *in, gzFile out)
{
	local char buf[BUFLEN];
	int len;

#ifdef USE_MMAP
	/* Try first compressing with mmap. If mmap fails (inflate used in a
	 * pipe), use the normal fread loop.
	 */
	if (gz_compress_mmap(in, out) == Z_OK)
		return;
#endif
	for (;;)
	{
		len = (int) fread(buf, 1, sizeof(buf), in);
		if (ferror(in))
		{
			perror("fread");
			exit(1);
		}
		if (len == 0)
			break;

		if (gzwrite(out, buf, (unsigned) len) != len)
		{
			int err;
			const char *msg;
			msg = gzerror(out, &err);
			error(msg, zError(err));
		}
	}
	fclose(in);
	if (gzclose(out) != Z_OK)
		error("failed gzclose", NULL);
}

#ifdef USE_MMAP							/* MMAP version, Miguel Albrecht <malbrech@eso.org> */

/* Try compressing the input file at once using mmap. Return Z_OK if
 * if success, Z_ERRNO otherwise.
 */
static int gz_compress_mmap(FILE *in, gzFile out)
{
	int len;
	int ifd = fileno(in);
	caddr_t buf;						/* mmap'ed buffer for the entire input file */
	off_t buf_len;						/* length of the input file */
	struct stat sb;

	/* Determine the size of the file, needed for mmap: */
	if (fstat(ifd, &sb) < 0)
		return Z_ERRNO;
	buf_len = sb.st_size;
	if (buf_len <= 0)
		return Z_ERRNO;

	/* Now do the actual mmap: */
	buf = mmap((caddr_t) 0, buf_len, PROT_READ, MAP_SHARED, ifd, (off_t) 0);
	if (buf == (caddr_t) (-1))
		return Z_ERRNO;

	/* Compress the whole file at once: */
	len = gzwrite(out, (char *) buf, (unsigned) buf_len);

	if (len != (int) buf_len)
	{
		int err;
		const char *msg;
		msg = gzerror(out, &err);
		error(msg, zError(err));
	}

	munmap(buf, buf_len);
	fclose(in);
	if (gzclose(out) != Z_OK)
		error("failed gzclose", NULL);
	return Z_OK;
}
#endif /* USE_MMAP */

/* ===========================================================================
 * Uncompress input to output then close both files.
 */
static void gz_uncompress(gzFile in, FILE *out)
{
	local char buf[BUFLEN];
	int len;

	for (;;)
	{
		len = (int) gzread(in, buf, (unsigned) sizeof(buf));
		if (len < 0)
		{
			int err;
			const char *msg;
			msg = gzerror(in, &err);
			error(msg, zError(err));
		}
		if (len == 0)
			break;

		if ((int) fwrite(buf, 1, (unsigned) len, out) != len)
		{
			error("failed fwrite", NULL);
		}
	}
	if (fclose(out))
		error("failed fclose", NULL);

	if (gzclose(in) != Z_OK)
		error("failed gzclose", NULL);
}


/* ===========================================================================
 * Compress the given file: create a corresponding .gz file and remove the
 * original.
 */
static void file_compress(const char *file, const char *mode)
{
	local char outfile[MAX_NAME_LEN];
	FILE *in;
	gzFile out;

	if (strlen(file) + strlen(GZ_SUFFIX) >= sizeof(outfile))
	{
		fprintf(stderr, "%s: filename too long\n", prog);
		exit(1);
	}

	strcpy(outfile, file);
	strcat(outfile, GZ_SUFFIX);

	in = fopen(file, "rb");
	if (in == NULL)
	{
		perror(file);
		exit(1);
	}
	out = gzopen(outfile, mode);
	if (out == NULL)
	{
		fprintf(stderr, "%s: can't gzopen %s\n", prog, outfile);
		exit(1);
	}
	gz_compress(in, out);

	unlink(file);
}


/* ===========================================================================
 * Uncompress the given file and remove the original.
 */
static void file_uncompress(const char *file)
{
	local char buf[MAX_NAME_LEN];
	const char *infile;
	const char *outfile;
	FILE *out;
	gzFile in;
	unsigned len = strlen(file);

	if (len + strlen(GZ_SUFFIX) >= sizeof(buf))
	{
		fprintf(stderr, "%s: filename too long\n", prog);
		exit(1);
	}

	strcpy(buf, file);

	if (len > SUFFIX_LEN && strcmp(file + len - SUFFIX_LEN, GZ_SUFFIX) == 0)
	{
		infile = file;
		outfile = buf;
		buf[len - 3] = '\0';
	} else
	{
		outfile = file;
		infile = buf;
		strcat(buf, GZ_SUFFIX);
	}
	in = gzopen(infile, "rb");
	if (in == NULL)
	{
		fprintf(stderr, "%s: can't gzopen %s\n", prog, infile);
		exit(1);
	}
	out = fopen(outfile, "wb");
	if (out == NULL)
	{
		perror(file);
		exit(1);
	}

	gz_uncompress(in, out);

	unlink(infile);
}


/* ===========================================================================
 */

static void usage(FILE *fp)
{
	fprintf(fp, "Usage: %s [-c] [-d] [-f] [-h] [-r] [-R] [-Z] [-1 to -9] [files...]\n", "miniinflate");
	fputs("options:\n", fp);
	fputs("    -c, --stdout      write to standard output\n", fp);
	fputs("    -d, --decompress  decompress\n", fp);
	fputs("    -f, --filtered    compress with Z_FILTERED\n", fp);
	fputs("    -h, --huffman     compress with Z_HUFFMAN_ONLY\n", fp);
	fputs("    -r, --rle         compress with Z_RLE\n", fp);
	fputs("    -R, --raw         compress raw\n", fp);
	fputs("    -Z, --zlib        compress with zlib header\n", fp);
	fputs("    -1, --fast        compress faster\n", fp);
	fputs("    -9, --best        compress better\n", fp);
}

static struct option const long_options[] = {
	{ "stdout", no_argument, NULL, 'c' },
	{ "decompress", no_argument, NULL, 'd' },
	{ "filtered", no_argument, NULL, 'f' },
	{ "huffman", no_argument, NULL, 'h' },
	{ "rle", no_argument, NULL, 'r' },
	{ "raw", no_argument, NULL, 'R' },
	{ "zlib", no_argument, NULL, 'Z' },
	{ "fast", no_argument, NULL, '1' },
	{ "best", no_argument, NULL, '9' },
	{ NULL, no_argument, NULL, 0 }
};

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	int copyout = 0;
	int uncompr = 0;
	gzFile file;
	char *bname;
	char outmode[20];
	int c;
	
#ifdef ZLIB_SLB
	long ret;

	if ((ret = slb_zlib_open(NULL)) < 0)
	{
		fprintf(stderr, "cannot load zlib.slb: %ld\n", ret);
		exit(1);
	}
#endif

	strcpy(outmode, "wb6  ");

	prog = argv[0];
	bname = strrchr(argv[0], '/');
	if (bname)
		bname++;
	else
		bname = argv[0];
	prog = bname;
	bname = strrchr(prog, '\\');
	if (bname)
		bname++;
	else
		bname = prog;
	prog = bname;

	mem_test_start();

	if (strcmp(bname, "gunzip") == 0)
		uncompr = 1;
	else if (strcmp(bname, "zcat") == 0)
		copyout = uncompr = 1;

	while ((c = getopt_long_only(argc, argv, "cdfhrRZ123456789", long_options, NULL)) >= 0)
	{
		switch (c)
		{
		case 'c':
			copyout = 1;
			break;
		case 'd':
			uncompr = 1;
			break;
		case 'f':
			outmode[3] = 'f';
			break;
		case 'h':
			outmode[3] = 'h';
			break;
		case 'r':
			outmode[3] = 'R';
			break;
		case 'R':
			outmode[4] = 'q';
			break;
		case 'Z':
			outmode[4] = 'z';
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			outmode[2] = c;
			break;
		default:
			usage(stderr);
			return 1;
		}
	}
	
	if (uncompr || copyout)
		outmode[0] = 'r';
	argv += optind;
	argc -= optind;
	if (argc == 0)
	{
		SET_BINARY_MODE(stdin);
		SET_BINARY_MODE(stdout);
		if (uncompr)
		{
			file = gzdopen(fileno(stdin), outmode);
			if (file == NULL)
				error("can't gzdopen stdin", NULL);
			gz_uncompress(file, stdout);
		} else
		{
			file = gzdopen(fileno(stdout), outmode);
			if (file == NULL)
				error("can't gzdopen stdout", NULL);
			gz_compress(stdin, file);
		}
	} else
	{
		if (copyout)
		{
			SET_BINARY_MODE(stdout);
		}
		do
		{
			if (uncompr)
			{
				if (copyout)
				{
					file = gzopen(*argv, outmode);
					if (file == NULL)
						fprintf(stderr, "%s: can't gzopen %s\n", prog, *argv);
					else
						gz_uncompress(file, stdout);
				} else
				{
					file_uncompress(*argv);
				}
			} else
			{
				if (copyout)
				{
					FILE *in = fopen(*argv, "rb");

					if (in == NULL)
					{
						perror(*argv);
					} else
					{
						file = gzdopen(fileno(stdout), outmode);
						if (file == NULL)
							error("can't gzdopen stdout", NULL);

						gz_compress(in, file);
					}

				} else
				{
					file_compress(*argv, outmode);
				}
			}
		} while (argv++, --argc);
	}

	mem_test_end();

	return 0;
}
