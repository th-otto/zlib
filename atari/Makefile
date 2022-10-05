# Makefile for zlib
# Copyright (C) 1995-2017 Jean-loup Gailly, Mark Adler
# For conditions of distribution and use, see copyright notice in zlib.h
# Modified for Atari shared library support

# To compile and test, type:
#    ./configure; make test
# Normally configure builds both a static and a shared library.
# If you want to build just a static library, use: ./configure --static

# To install /usr/local/lib/libz.* and /usr/local/include/zlib.h, type:
#    make install
# To install in $HOME instead of /usr/local, use:
#    make install prefix=$HOME

CROSS_PREFIX=m68k-atari-mint-

CC = $(CROSS_PREFIX)gcc

CPU_CFLAGS=-m68020-60
CFLAGS=-O2 -Wall -fomit-frame-pointer -Wstrict-prototypes -Wmissing-prototypes -Werror $(CPU_CFLAGS)
CPPFLAGS= -D_LARGEFILE64_SOURCE=1 $(ZINCOUT)
SFLAGS=$(CFLAGS) -DZLIB_SLB
LDFLAGS=
TEST_LDFLAGS=-L. $(STATICLIB)
LDSHARED=$(CC) -s -nostartfiles -Wl,--mprg-flags,0x0f

STATICLIB=libz.a
SHAREDLIB=zlib.slb
SHAREDLIBV=$(SHAREDLIB)
SHAREDLIBM=
IMPORTLIB=libz.slb.a
SHAREDTARGET=$(SHAREDLIBV)
LIBS=$(STATICLIB) $(SHAREDTARGET)


CPP=$(CC) -E -P
AR=$(CROSS_PREFIX)ar
ARFLAGS=rcs
RANLIB=$(CROSS_PREFIX)ranlib
STRIP=$(CROSS_PREFIX)strip
LDSHAREDLIBC= -nostdlib -lgcc
TAR=tar
SHELL=/bin/sh
EXE=
AWK=awk

prefix =/usr
exec_prefix =${prefix}
libdir =${exec_prefix}/lib
bindir =${exec_prefix}/bin
sharedlibdir =${prefix}/../mint/slb
includedir =${prefix}/include
mandir =${prefix}/share/man
man3dir = ${mandir}/man3
pkgconfigdir = ${libdir}/pkgconfig
SRCDIR=../
ZINC=
ZINCOUT=-I. -I.. -I$(SRCDIR)contrib/minizip

OBJZ = adler32.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o zutil.o
OBJG = compress.o uncompr.o gzclose.o gzlib.o gzread.o gzwrite.o
OBJM = ioapi.o zip.o unzip.o iowin32.o
OBJC = $(OBJZ) $(OBJG) $(OBJM)

PIC_OBJZ = header.lo zlibslb.lo zlibinit.lo adler32.lo crc32.lo deflate.lo infback.lo inffast.lo inflate.lo inftrees.lo trees.lo zutil.lo
PIC_OBJG = compress.lo uncompr.lo gzclose.lo gzlib.lo gzread.lo gzwrite.lo
PIC_OBJM = ioapi.lo zip.lo unzip.lo iowin32.lo
PIC_OBJC = $(PIC_OBJZ) $(PIC_OBJG) $(PIC_OBJM)

OBJS = $(OBJC)

PIC_OBJS = $(PIC_OBJC)

GEN_IMP_OBJS = \
	zimp_0.o \
	zimp_1.o \
	zimp_2.o \
	zimp_3.o \
	zimp_4.o \
	zimp_5.o \
	zimp_6.o \
	zimp_7.o \
	zimp_8.o \
	zimp_9.o \
	zimp_10.o \
	zimp_11.o \
	zimp_12.o \
	zimp_13.o \
	zimp_14.o \
	zimp_15.o \
	zimp_16.o \
	zimp_17.o \
	zimp_18.o \
	zimp_19.o \
	zimp_20.o \
	zimp_21.o \
	zimp_22.o \
	zimp_23.o \
	zimp_24.o \
	zimp_25.o \
	zimp_26.o \
	zimp_27.o \
	zimp_28.o \
	zimp_29.o \
	zimp_30.o \
	zimp_31.o \
	zimp_32.o \
	zimp_33.o \
	zimp_34.o \
	zimp_35.o \
	zimp_36.o \
	zimp_37.o \
	zimp_38.o \
	zimp_39.o \
	zimp_40.o \
	zimp_41.o \
	zimp_42.o \
	zimp_43.o \
	zimp_44.o \
	zimp_45.o \
	zimp_46.o \
	zimp_47.o \
	zimp_48.o \
	zimp_49.o \
	zimp_50.o \
	zimp_51.o \
	zimp_52.o \
	\
	zimp_61.o \
	zimp_62.o \
	zimp_63.o \
	zimp_64.o \
	zimp_65.o \
	zimp_66.o \
	zimp_67.o \
	zimp_68.o \
	zimp_69.o \
	zimp_70.o \
	zimp_71.o \
	zimp_72.o \
	zimp_73.o \
	zimp_74.o \
	zimp_75.o \
	zimp_76.o \
	zimp_77.o \
	zimp_78.o \
	zimp_79.o \
	zimp_80.o \
	zimp_81.o \
	zimp_82.o \
	zimp_83.o \
	zimp_84.o \
	\
	zimp_86.o \
	zimp_87.o \
	zimp_88.o \
	zimp_89.o \
	\
	zimp_100.o \
	zimp_101.o \
	\
	zimp_120.o \
	zimp_121.o \
	zimp_122.o \
	\
	zimp_124.o \
	zimp_125.o \
	zimp_126.o \
	zimp_127.o \
	zimp_128.o \
	\
	zimp_130.o \
	zimp_131.o \
	zimp_132.o \
	zimp_133.o \
	zimp_134.o \
	zimp_135.o \
	zimp_136.o \
	\
	zimp_140.o \
	zimp_141.o \
	zimp_142.o \
	zimp_143.o \
	zimp_144.o \
	zimp_145.o \
	zimp_146.o \
	zimp_147.o \
	zimp_148.o \
	zimp_149.o \
	zimp_150.o \
	zimp_151.o \
	zimp_152.o \
	zimp_153.o \
	zimp_154.o \
	\
	zimp_156.o \
	zimp_157.o \
	zimp_158.o \
	zimp_159.o \
	zimp_160.o \
	zimp_161.o \
	\
	zimp_163.o \
	zimp_164.o \
	\
	zimp_166.o \
	zimp_167.o \
	zimp_168.o \
	zimp_169.o \
	zimp_170.o \
	zimp_171.o \
	zimp_172.o \
	zimp_173.o \
	zimp_174.o \
	zimp_175.o \
	zimp_176.o \
	zimp_177.o \
	zimp_178.o \
	$(empty)
IMP_OBJS = zimpptr.o zimpopen.o libclose.o slbload.o slbexec.o \
	$(GEN_IMP_OBJS)

all: static shared all64

static: $(STATICLIB) example$(EXE) minigzip$(EXE)

shared: $(SHAREDLIB) $(GEN_IMP_OBJS:.o=.c) $(IMPORTLIB) examplesh$(EXE) minigzipsh$(EXE)

$(GEN_IMP_OBJS:.o=.c): genimp.awk exports.h
	$(AWK) -f ./genimp.awk exports.h

all64: example64$(EXE) minigzip64$(EXE)

check: test

test: all teststatic test64

teststatic: static
	@TMPST=tmpst_$$; \
	if echo hello world | ./minigzip | ./minigzip -d && ./example $$TMPST ; then \
	  echo '		*** zlib test OK ***'; \
	else \
	  echo '		*** zlib test FAILED ***'; false; \
	fi; \
	rm -f $$TMPST

testshared: shared
	@LD_LIBRARY_PATH=`pwd`:$(LD_LIBRARY_PATH) ; export LD_LIBRARY_PATH; \
	LD_LIBRARYN32_PATH=`pwd`:$(LD_LIBRARYN32_PATH) ; export LD_LIBRARYN32_PATH; \
	DYLD_LIBRARY_PATH=`pwd`:$(DYLD_LIBRARY_PATH) ; export DYLD_LIBRARY_PATH; \
	SHLIB_PATH=`pwd`:$(SHLIB_PATH) ; export SHLIB_PATH; \
	TMPSH=tmpsh_$$; \
	if echo hello world | ./minigzipsh | ./minigzipsh -d && ./examplesh $$TMPSH; then \
	  echo '		*** zlib shared test OK ***'; \
	else \
	  echo '		*** zlib shared test FAILED ***'; false; \
	fi; \
	rm -f $$TMPSH

test64: all64
	@TMP64=tmp64_$$; \
	if echo hello world | ./minigzip64 | ./minigzip64 -d && ./example64 $$TMP64; then \
	  echo '		*** zlib 64-bit test OK ***'; \
	else \
	  echo '		*** zlib 64-bit test FAILED ***'; false; \
	fi; \
	rm -f $$TMP64

infcover.o: $(SRCDIR)test/infcover.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -DZLIB_STATIC -c -o $@ $<

infcover$(EXE): infcover.o $(STATICLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ infcover.o $(STATICLIB)

cover: infcover$(EXE)
	rm -f *.gcda
	./infcover$(EXE)
	gcov inf*.c

$(STATICLIB): $(OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

zimpopen.o: zlibstr.h

$(IMPORTLIB): $(IMP_OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

$(IMP_OBJS): zlib_imp.h

example.o: $(SRCDIR)test/example.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_STATIC -c -o $@ $<

example.lo: $(SRCDIR)test/example.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_SLB -c -o $@ $<

minigzip.o: $(SRCDIR)test/minigzip.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_STATIC -c -o $@ $<

minigzip.lo: $(SRCDIR)test/minigzip.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_SLB -c -o $@ $<

example64.o: $(SRCDIR)test/example.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_STATIC -D_FILE_OFFSET_BITS=64 -c -o $@ $<

example64.lo: $(SRCDIR)test/example.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -D_FILE_OFFSET_BITS=64 -c -o $@ $(SRCDIR)test/example.c

minigzip64.o: $(SRCDIR)test/minigzip.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_STATIC -D_FILE_OFFSET_BITS=64 -c -o $@ $<

minigzip64.lo: $(SRCDIR)test/minigzip.c $(SRCDIR)zlib.h $(SRCDIR)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -D_FILE_OFFSET_BITS=64 -c -o $@ $<


adler32.o: $(SRCDIR)adler32.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

crc32.o: $(SRCDIR)crc32.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

deflate.o: $(SRCDIR)deflate.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

infback.o: $(SRCDIR)infback.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

inffast.o: $(SRCDIR)inffast.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

inflate.o: $(SRCDIR)inflate.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

inftrees.o: $(SRCDIR)inftrees.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

trees.o: $(SRCDIR)trees.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

zutil.o: $(SRCDIR)zutil.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

compress.o: $(SRCDIR)compress.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

uncompr.o: $(SRCDIR)uncompr.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

gzclose.o: $(SRCDIR)gzclose.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

gzlib.o: $(SRCDIR)gzlib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

gzread.o: $(SRCDIR)gzread.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

gzwrite.o: $(SRCDIR)gzwrite.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

ioapi.o: $(SRCDIR)contrib/minizip/ioapi.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

iowin32.o: $(SRCDIR)contrib/minizip/iowin32.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

zip.o: $(SRCDIR)contrib/minizip/zip.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

unzip.o: $(SRCDIR)contrib/minizip/unzip.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<


slbexec.o: slbexec.S
	$(CC) $(CFLAGS) -Wa,--mri $(CPPFLAGS) -D_BasPag=__base -c -o $@ $<


header.lo: header.S
	$(CC) $(SFLAGS) $(CPPFLAGS) -DSHAREDLIB=\"$(SHAREDLIB)\" -c -o $@ $<

zlibver.h: $(SRCDIR)zlib.h
	grep ZLIB_VERNUM $< > $@

zlibinit.lo: zlibinit.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

zlibslb.lo: zlibslb.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

adler32.lo: $(SRCDIR)adler32.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

crc32.lo: $(SRCDIR)crc32.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

deflate.lo: $(SRCDIR)deflate.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

infback.lo: $(SRCDIR)infback.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

inffast.lo: $(SRCDIR)inffast.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

inflate.lo: $(SRCDIR)inflate.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

inftrees.lo: $(SRCDIR)inftrees.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

trees.lo: $(SRCDIR)trees.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

zutil.lo: $(SRCDIR)zutil.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

compress.lo: $(SRCDIR)compress.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

uncompr.lo: $(SRCDIR)uncompr.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

gzclose.lo: $(SRCDIR)gzclose.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

gzlib.lo: $(SRCDIR)gzlib.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

gzread.lo: $(SRCDIR)gzread.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

gzwrite.lo: $(SRCDIR)gzwrite.c
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

ioapi.lo: $(SRCDIR)contrib/minizip/ioapi.c zlibslb.h
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

iowin32.lo: $(SRCDIR)contrib/minizip/iowin32.c zlibslb.h
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

zip.lo: $(SRCDIR)contrib/minizip/zip.c zlibslb.h
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

unzip.lo: $(SRCDIR)contrib/minizip/unzip.c zlibslb.h
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<


$(SHAREDTARGET): $(PIC_OBJS) $(STATICLIB)
	$(LDSHARED) $(SFLAGS) $(CPPFLAGS) -o $@ $(PIC_OBJS) $(LDSHAREDLIBC) $(LDFLAGS) $(EXTRA_LDFLAGS)
	stripex $@

example$(EXE): example.o $(STATICLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -o $@ example.o $(TEST_LDFLAGS) $(EXTRA_LDFLAGS)

minigzip$(EXE): minigzip.o $(STATICLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -o $@ minigzip.o $(TEST_LDFLAGS) $(EXTRA_LDFLAGS)

examplesh$(EXE): example.lo $(IMPORTLIB) $(SHAREDTARGET)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -o $@ example.lo -L. -lz.slb $(EXTRA_LDFLAGS)

minigzipsh$(EXE): minigzip.lo $(IMPORTLIB) $(SHAREDTARGET)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -o $@ minigzip.lo -L. -lz.slb $(EXTRA_LDFLAGS)

example64$(EXE): example64.o $(STATICLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -o $@ example64.o $(TEST_LDFLAGS) $(EXTRA_LDFLAGS)

minigzip64$(EXE): minigzip64.o $(STATICLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -o $@ minigzip64.o $(TEST_LDFLAGS) $(EXTRA_LDFLAGS)

install-libs: $(LIBS) zlib.pc
	-@if [ ! -d $(DESTDIR)$(exec_prefix)  ]; then mkdir -p $(DESTDIR)$(exec_prefix); fi
	-@if [ ! -d $(DESTDIR)$(libdir)       ]; then mkdir -p $(DESTDIR)$(libdir); fi
	-@if [ ! -d $(DESTDIR)$(sharedlibdir) ]; then mkdir -p $(DESTDIR)$(sharedlibdir); fi
	-@if [ ! -d $(DESTDIR)$(man3dir)      ]; then mkdir -p $(DESTDIR)$(man3dir); fi
	-@if [ ! -d $(DESTDIR)$(pkgconfigdir) ]; then mkdir -p $(DESTDIR)$(pkgconfigdir); fi
	test -z "$(STATICLIB)" || rm -f $(DESTDIR)$(libdir)/$(STATICLIB)
	test -z "$(IMPORTLIB)" || rm -f $(DESTDIR)$(libdir)/$(IMPORTLIB)
	install -m 644 $(STATICLIB) $(IMPORTLIB) $(DESTDIR)$(libdir)
	-@($(RANLIB) $(DESTDIR)$(libdir)/$(STATICLIB) || true) >/dev/null 2>&1
	rm -f $(DESTDIR)$(sharedlibdir)/$(SHAREDTARGET); \
	echo "install $(SHAREDTARGET) $(DESTDIR)$(sharedlibdir)"; \
	install -m 755 $(SHAREDTARGET) $(DESTDIR)$(sharedlibdir); \
	rm -f $(DESTDIR)$(man3dir)/zlib.3
	install -m 644 $(SRCDIR)zlib.3 $(DESTDIR)$(man3dir)
	rm -f $(DESTDIR)$(pkgconfigdir)/zlib.pc
	install -m 644 zlib.pc $(DESTDIR)$(pkgconfigdir)
# The ranlib in install is needed on NeXTSTEP which checks file times

install: install-libs
	-@if [ ! -d $(DESTDIR)$(includedir)   ]; then mkdir -p $(DESTDIR)$(includedir); fi
	-@if [ ! -d $(DESTDIR)$(includedir)/slb   ]; then mkdir -p $(DESTDIR)$(includedir)/slb; fi
	rm -f $(DESTDIR)$(includedir)/zlib.h $(DESTDIR)$(includedir)/zconf.h $(DESTDIR)$(includedir)/slb/zlib.h
	install -m 644 $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(DESTDIR)$(includedir)
	install -m 644 slb/zlib.h $(DESTDIR)$(includedir)/slb

zlib.pc: Makefile
	@( \
	 VERSION=`sed -n -e '/VERSION "/s/.*"\(.*\)".*/\1/p' ${SRCDIR}zlib.h`; \
	 echo "prefix=$(prefix)"; \
	 echo 'exec_prefix=$${prefix}'; \
	 echo 'libdir=$${exec_prefix}/lib'; \
	 echo 'bindir=$${exec_prefix}/bin'; \
	 echo 'includedir=$${prefix}/include'; \
	 echo 'sharedlibdir=$${prefix}/../mint/slb'; \
	 echo ""; \
	 echo "Name: zlib"; \
	 echo "Description: zlib compression library"; \
	 echo "Version: $${VERSION}"; \
	 echo "Requires: "; \
	 echo "Libs: -lz.slb"; \
	 echo "Libs.private: "; \
	 echo "Cflags: -DZLIB_SLB"; \
	) > $@


install-strip: install
	$(STRIP) -g -x $(DESTDIR)$(libdir)/$(STATICLIB)
	$(RANLIB) $(DESTDIR)$(libdir)/$(STATICLIB)
	$(STRIP) -g -x $(DESTDIR)$(libdir)/$(IMPORTLIB)
	$(RANLIB) $(DESTDIR)$(libdir)/$(IMPORTLIB)

uninstall:
	cd $(DESTDIR)$(includedir) && rm -f zlib.h zconf.h slb/zlib.h
	cd $(DESTDIR)$(libdir) && rm -f $(STATICLIB) $(IMPORTLIB); \
	if test -n "$(SHAREDLIBV)" -a -f $(SHAREDLIBV); then \
	  rm -f $(SHAREDLIBV) $(SHAREDLIB) $(SHAREDLIBM); \
	fi
	cd $(DESTDIR)$(man3dir) && rm -f zlib.3
	cd $(DESTDIR)$(pkgconfigdir) && rm -f zlib.pc
	cd $(DESTDIR)$(sharedlibdir); (rm -f $(SHAREDTARGET) || true) > /dev/null 2>&1

docs: zlib.3.pdf


GFA_INL = \
	gfa/strcat.inl \
	gfa/strcmp.inl \
	gfa/strcpy.inl \
	gfa/strlen.inl \
	gfa/memchr.inl \
	gfa/memcpy.inl \
	gfa/memset.inl \
	gfa/strerror.inl \
	gfa/malloc.inl \
	gfa/free.inl \
	$(empty)

GFA_OTHER = \
	gfa/zlib.lst \
	gfa/zlib.gfa \
	gfa/slbload.lst \
	gfa/utils.lst \
	gfa/zlibtest.gfa \
	gfa/example.gfa \
	gfa/example.lst \
	gfa/usepkzip.gfa \
	gfa/usepkzip.lst \
	$(empty)

gfa/minilib.inl: $(GFA_INL)
	cat $(GFA_INL) > $@

zlib.3.pdf: $(SRCDIR)zlib.3
	groff -mandoc -f H -T ps $(SRCDIR)zlib.3 | ps2pdf - $@

bindist: gfa/minilib.inl
	$(MAKE) DESTDIR=/tmp/t/zlib PUREC=/windows/c/atari/pc/lib allbindist

allbindist:
	$(MAKE) clean
	$(MAKE) -j8 CPU_CFLAGS="-m68020-60"
	$(MAKE) libdir="$(libdir)/m68020-60" sharedlibdir=$(sharedlibdir)/020 install
	rm -rf $(DESTDIR)$(libdir)/m68020-60/pkgconfig
	$(MAKE) clean
	$(MAKE) -j8 CPU_CFLAGS="-mcpu=5475"
	$(MAKE) libdir="$(libdir)/m5475" sharedlibdir=$(sharedlibdir)/v4e install
	rm -rf $(DESTDIR)$(libdir)/m5475/pkgconfig
	$(MAKE) clean
	$(MAKE) -j8 CPU_CFLAGS="-m68000"
	$(MAKE) libdir="$(libdir)" sharedlibdir=$(sharedlibdir)/000 install
	install -m 755 $(SHAREDTARGET) $(DESTDIR)$(sharedlibdir)
	install -d $(DESTDIR)$(bindir)
	$(STRIP) example examplesh minigzip minigzipsh
	install -m 755 example examplesh minigzip minigzipsh $(DESTDIR)$(bindir)
	rm -f $(DESTDIR)$(mandir)/*/*.gz
	gzip $(DESTDIR)$(mandir)/*/*
	install -d $(DESTDIR)/purec/include/slb $(DESTDIR)/purec/lib/000 $(DESTDIR)/purec/lib/020 $(DESTDIR)/purec/bin
	install -m 644 $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(DESTDIR)/purec/include
	install -m 644 slb/zlib.h $(DESTDIR)/purec/include/slb
	cd $(DESTDIR)/purec/include && cr2nl -R -d .
	install -m 644 $(PUREC)/000/zlib.lib $(PUREC)/000/zlibslb.lib $(DESTDIR)/purec/lib/000
	install -m 644 $(PUREC)/020/zlib.lib $(PUREC)/020/zlibslb.lib $(DESTDIR)/purec/lib/020
	install -d $(DESTDIR)/gfa
	install -m 644 gfa/minilib.inl $(GFA_INL) $(GFA_OTHER) $(DESTDIR)/gfa
	$(MAKE) clean
	install -m 644 READ_SLB.txt $(DESTDIR)
	VERSION=`sed -n -e '/VERSION "/s/.*"\(.*\)".*/\1/p' $(SRCDIR)zlib.h | tr -d .`; cd $(DESTDIR)/..; rm -f zlib$${VERSION}.zip; zip -r zlib$${VERSION}.zip `basename $(DESTDIR)`
	cd $(SRCDIR); VERSION=`sed -n -e '/VERSION "/s/.*"\(.*\)".*/\1/p' zlib.h`; git archive --prefix=zlib-$${VERSION}-slb/ HEAD | bzip2 > $(DESTDIR)/../zlib-$${VERSION}-slb.tar.bz2

mostlyclean: clean
clean:
	rm -f *.o *.lo *~ zlib.pc \
	   $(GEN_IMP_OBJS:.o=.c) \
	   example$(EXE) minigzip$(EXE) examplesh$(EXE) minigzipsh$(EXE) \
	   example64$(EXE) minigzip64$(EXE) infcover$(EXE) \
	   $(STATICLIB) $(IMPORTLIB) $(SHAREDTARGET) $(SHAREDLIBV) $(SHAREDLIBV) $(SHAREDLIBM) \
	   libz.* foo.gz so_locations \
	   maketree contrib/infback9/*.o
	rm -f *.gcda *.gcno *.gcov
	rm -f contrib/infback9/*.gcda contrib/infback9/*.gcno contrib/infback9/*.gcov

maintainer-clean: distclean
distclean: clean zconf docs
	rm -f Makefile zlib.pc configure.log
	-@rm -f .DS_Store
	@if [ -f Makefile.in ]; then \
	printf 'all:\n\t-@echo "Please use ./configure first.  Thank you."\n' > Makefile ; \
	printf '\ndistclean:\n\tmake -f Makefile.in distclean\n' >> Makefile ; \
	touch -r $(SRCDIR)Makefile.in Makefile ; fi
	@if [ ! -f zlib.3 ]; then rm -f zlib.3.pdf ; fi
	rm -f zlibver.h

tags:
	etags $(SRCDIR)*.[ch]

headerpc.s: header.S exports.h symbols.h zlibver.h Makefile
	$(CPP) $(CPPFLAGS) -U__USER_LABEL_PREFIX__ -D__USER_LABEL_PREFIX__= $< | sed -e 's/;/\n /g' -e 's/%//g' -e 's/jbra/jmp/' -e 's/SHAREDLIB/"$(SHAREDLIB)"/' > $@

adler32.o zutil.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h
gzclose.o gzlib.o gzread.o gzwrite.o: $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)gzguts.h
compress.o example.o minigzip.o uncompr.o: $(SRCDIR)zlib.h $(SRCDIR)zconf.h
crc32.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)crc32.h
deflate.o: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h
infback.o inflate.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h $(SRCDIR)inffixed.h
inffast.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h
inftrees.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h
trees.o: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)trees.h

adler32.lo zutil.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h zlibslb.h zlibstr.h
gzclose.lo gzlib.lo gzread.lo gzwrite.lo: $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)gzguts.h zlibslb.h zlibstr.h
compress.lo example.lo minigzip.lo uncompr.lo: $(SRCDIR)zlib.h $(SRCDIR)zconf.h zlibslb.h zlibstr.h
crc32.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)crc32.h zlibslb.h zlibstr.h
deflate.lo: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h zlibslb.h zlibstr.h
infback.lo inflate.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h $(SRCDIR)inffixed.h zlibslb.h zlibstr.h
inffast.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h zlibslb.h zlibstr.h
inftrees.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h zlibslb.h zlibstr.h
trees.lo: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)trees.h zlibslb.h zlibstr.h

zlibinit.lo: exports.h zlibslb.h zlibstr.h
header.lo: exports.h symbols.h zlibver.h
