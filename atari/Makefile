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

CFLAGS=-O3 -Wall -fomit-frame-pointer
CPPFLAGS= -D_LARGEFILE64_SOURCE=1 $(ZINCOUT) -DSHAREDLIB=\"$(SHAREDLIB)\"
SFLAGS=$(CFLAGS) -DZLIB_SLB
LDFLAGS=
TEST_LDFLAGS=-L. $(STATICLIB)
LDSHARED=$(CC) -s -nostartfiles -Wl,--mprg-flags,0x0f

STATICLIB=libz.a
SHAREDLIB=zlib.slb
SHAREDLIBV=$(SHAREDLIB)
SHAREDLIBM=
IMPORTLIB=libz.slb.a
SHAREDLIBPOST=
SHAREDTARGET=$(SHAREDLIBV)
LIBS=$(STATICLIB) $(SHAREDTARGET)


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

PIC_OBJZ = header.lo zlibinit.lo adler32.lo crc32.lo deflate.lo infback.lo inffast.lo inflate.lo inftrees.lo trees.lo zutil.lo
PIC_OBJG = compress.lo uncompr.lo gzclose.lo gzlib.lo gzread.lo gzwrite.lo
PIC_OBJM = ioapi.lo zip.lo unzip.lo iowin32.lo
PIC_OBJC = $(PIC_OBJZ) $(PIC_OBJG) $(PIC_OBJM)

OBJS = $(OBJC)

PIC_OBJS = $(PIC_OBJC)

GEN_IMP_OBJS = \
	zlib_imp_0.o \
	zlib_imp_1.o \
	zlib_imp_2.o \
	zlib_imp_3.o \
	zlib_imp_4.o \
	zlib_imp_5.o \
	zlib_imp_6.o \
	zlib_imp_7.o \
	zlib_imp_8.o \
	zlib_imp_9.o \
	zlib_imp_10.o \
	zlib_imp_11.o \
	zlib_imp_12.o \
	zlib_imp_13.o \
	zlib_imp_14.o \
	zlib_imp_15.o \
	zlib_imp_16.o \
	zlib_imp_17.o \
	zlib_imp_18.o \
	zlib_imp_19.o \
	zlib_imp_20.o \
	zlib_imp_21.o \
	zlib_imp_22.o \
	zlib_imp_23.o \
	zlib_imp_24.o \
	zlib_imp_25.o \
	zlib_imp_26.o \
	zlib_imp_27.o \
	zlib_imp_28.o \
	zlib_imp_29.o \
	zlib_imp_30.o \
	zlib_imp_31.o \
	zlib_imp_32.o \
	zlib_imp_33.o \
	zlib_imp_34.o \
	zlib_imp_35.o \
	zlib_imp_36.o \
	zlib_imp_37.o \
	zlib_imp_38.o \
	zlib_imp_39.o \
	zlib_imp_40.o \
	zlib_imp_41.o \
	zlib_imp_42.o \
	zlib_imp_43.o \
	zlib_imp_44.o \
	zlib_imp_45.o \
	zlib_imp_46.o \
	zlib_imp_47.o \
	zlib_imp_48.o \
	zlib_imp_49.o \
	zlib_imp_50.o \
	zlib_imp_51.o \
	zlib_imp_52.o \
	\
	zlib_imp_61.o \
	zlib_imp_62.o \
	zlib_imp_63.o \
	zlib_imp_64.o \
	zlib_imp_65.o \
	zlib_imp_66.o \
	zlib_imp_67.o \
	zlib_imp_68.o \
	zlib_imp_69.o \
	zlib_imp_70.o \
	zlib_imp_71.o \
	zlib_imp_72.o \
	zlib_imp_73.o \
	zlib_imp_74.o \
	zlib_imp_75.o \
	zlib_imp_76.o \
	zlib_imp_77.o \
	zlib_imp_78.o \
	zlib_imp_79.o \
	zlib_imp_80.o \
	zlib_imp_81.o \
	zlib_imp_82.o \
	zlib_imp_83.o \
	zlib_imp_84.o \
	\
	zlib_imp_86.o \
	zlib_imp_87.o \
	zlib_imp_88.o \
	zlib_imp_89.o \
	\
	zlib_imp_100.o \
	zlib_imp_101.o \
	\
	zlib_imp_120.o \
	zlib_imp_121.o \
	zlib_imp_122.o \
	\
	zlib_imp_124.o \
	zlib_imp_125.o \
	zlib_imp_126.o \
	zlib_imp_127.o \
	zlib_imp_128.o \
	\
	zlib_imp_130.o \
	zlib_imp_131.o \
	zlib_imp_132.o \
	zlib_imp_133.o \
	zlib_imp_134.o \
	zlib_imp_135.o \
	zlib_imp_136.o \
	\
	zlib_imp_140.o \
	zlib_imp_141.o \
	zlib_imp_142.o \
	zlib_imp_143.o \
	zlib_imp_144.o \
	zlib_imp_145.o \
	zlib_imp_146.o \
	zlib_imp_147.o \
	zlib_imp_148.o \
	zlib_imp_149.o \
	zlib_imp_150.o \
	zlib_imp_151.o \
	zlib_imp_152.o \
	zlib_imp_153.o \
	zlib_imp_154.o \
	\
	zlib_imp_156.o \
	zlib_imp_157.o \
	zlib_imp_158.o \
	zlib_imp_159.o \
	zlib_imp_160.o \
	zlib_imp_161.o \
	\
	zlib_imp_163.o \
	zlib_imp_164.o \
	\
	zlib_imp_166.o \
	zlib_imp_167.o \
	zlib_imp_168.o \
	zlib_imp_169.o \
	zlib_imp_170.o \
	zlib_imp_171.o \
	zlib_imp_172.o \
	zlib_imp_173.o \
	zlib_imp_174.o \
	zlib_imp_175.o \
	$(empty)
IMP_OBJS = zlib_imp_ptr.o zlib_imp_open.o \
	$(GEN_IMP_OBJS)

all: static shared all64

static: $(STATICLIB) example$(EXE) minigzip$(EXE)

shared: $(SHAREDLIB) $(GEN_IMP_OBJS:.o=.c) $(IMPORTLIB) examplesh$(EXE) minigzipsh$(EXE)

$(GEN_IMP_OBJS:.o=.c): genimp.awk zlib_exports.h
	$(AWK) -f ./genimp.awk zlib_exports.h

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

zlib_imp_open.o: zlibstruct.h

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



header.lo: header.S
	$(CC) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<
zlib_vernum.h: $(SRCDIR)zlib.h
	grep ZLIB_VERNUM $< > $@

zlibinit.lo: zlibinit.c
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


placebo $(SHAREDTARGET): $(PIC_OBJS) $(STATICLIB)
	$(LDSHARED) $(SFLAGS) $(CPPFLAGS) -o $@ $(PIC_OBJS) $(LDSHAREDLIBC) $(LDFLAGS) $(EXTRA_LDFLAGS)
	$(SHAREDLIBPOST)

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

zlib.3.pdf: $(SRCDIR)zlib.3
	groff -mandoc -f H -T ps $(SRCDIR)zlib.3 | ps2pdf - $@

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
	rm -f zlib_vernum.h

tags:
	etags $(SRCDIR)*.[ch]

adler32.o zutil.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h
gzclose.o gzlib.o gzread.o gzwrite.o: $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)gzguts.h
compress.o example.o minigzip.o uncompr.o: $(SRCDIR)zlib.h $(SRCDIR)zconf.h
crc32.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)crc32.h
deflate.o: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h
infback.o inflate.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h $(SRCDIR)inffixed.h
inffast.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h
inftrees.o: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h
trees.o: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)trees.h

adler32.lo zutil.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h zlibslb.h zlibstruct.h
gzclose.lo gzlib.lo gzread.lo gzwrite.lo: $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)gzguts.h zlibslb.h zlibstruct.h
compress.lo example.lo minigzip.lo uncompr.lo: $(SRCDIR)zlib.h $(SRCDIR)zconf.h zlibslb.h zlibstruct.h
crc32.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)crc32.h zlibslb.h zlibstruct.h
deflate.lo: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h zlibslb.h zlibstruct.h
infback.lo inflate.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h $(SRCDIR)inffixed.h zlibslb.h zlibstruct.h
inffast.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h $(SRCDIR)inflate.h $(SRCDIR)inffast.h zlibslb.h zlibstruct.h
inftrees.lo: $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)inftrees.h zlibslb.h zlibstruct.h
trees.lo: $(SRCDIR)deflate.h $(SRCDIR)zutil.h $(SRCDIR)zlib.h $(SRCDIR)zconf.h $(SRCDIR)trees.h zlibslb.h zlibstruct.h

zlibinit.lo: zlib_exports.h zlibslb.h zlibstruct.h
header.lo: zlib_exports.h symbols.h zlib_vernum.h
