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
WARN = -Wall -Wstrict-prototypes -Wmissing-prototypes -Wdeclaration-after-statement -Werror
CFLAGS=-O2 -fomit-frame-pointer $(WARN) $(CPU_CFLAGS)
CPPFLAGS= -D_LARGEFILE64_SOURCE=1 $(ZINCOUT)
SFLAGS=-DZLIB_SLB
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

srcdir = .
top_srcdir=../

prefix =/usr
exec_prefix =${prefix}
libdir =${exec_prefix}/lib
bindir =${exec_prefix}/bin
sharedlibdir =${prefix}/../mint/slb
includedir =${prefix}/include
mandir =${prefix}/share/man
man3dir = ${mandir}/man3
pkgconfigdir = ${libdir}/pkgconfig
ZINC=
ZINCOUT=-I. -I.. -I$(top_srcdir)contrib/minizip

LIB_SRCS = \
	$(top_srcdir)adler32.c \
	$(top_srcdir)crc32.c \
	$(top_srcdir)deflate.c \
	$(top_srcdir)infback.c \
	$(top_srcdir)inffast.c \
	$(top_srcdir)inflate.c \
	$(top_srcdir)inftrees.c \
	$(top_srcdir)trees.c \
	$(top_srcdir)zutil.c \
	$(top_srcdir)compress.c \
	$(top_srcdir)uncompr.c \
	$(top_srcdir)gzclose.c \
	$(top_srcdir)gzlib.c \
	$(top_srcdir)gzread.c \
	$(top_srcdir)gzwrite.c \
	$(top_srcdir)contrib/minizip/ioapi.c \
	$(top_srcdir)contrib/minizip/zip.c \
	$(top_srcdir)contrib/minizip/unzip.c \
	$(top_srcdir)contrib/minizip/iowin32.c \
	$(empty)

ALL_SRCS = \
	$(LIB_SRCS) \
	$(top_srcdir)test/example.c \
	$(top_srcdir)test/minigzip.c \
	$(top_srcdir)test/infcover.c \
	$(empty)

LIB_OBJS = $(subst .c,.o,$(notdir $(LIB_SRCS)))

PIC_OBJS = header.lo zlibslb.lo zlibinit.lo $(LIB_OBJS:.o=.lo)

GEN_IMP_SRCS := $(foreach num,$(shell seq 0 199),zimp_$(num).c)
GEN_IMP_OBJS := $(GEN_IMP_SRCS:.c=.o)

all: static shared all64

IMP_OBJS = zimpptr.o zimpopen.o libclose.o slbload.o slbexec.o $(GEN_IMP_OBJS)
zimpopen.o libclose.o: zlibstr.h zlibver.h

static: $(STATICLIB) example$(EXE) minigzip$(EXE)

shared: .genimpsources $(SHAREDLIB) $(IMPORTLIB) examplesh$(EXE) minigzipsh$(EXE)

.genimpsources: $(srcdir)/genimp.awk $(srcdir)/exports.h
	$(AWK) -f $(srcdir)/genimp.awk exports.h
	touch $@

define OBJ_template =
$(notdir $(basename $(1))).o: $(1)
	$(CC) $(CFLAGS) -DZLIB_STATIC $(INCLUDES) $(CPPFLAGS) -c $$< -o $$@

$(notdir $(basename $(1))).lo: $(1)
	$(CC) $(CFLAGS) $(SFLAGS) $(INCLUDES) $(CPPFLAGS) -c $$< -o $$@

endef

$(foreach file,$(ALL_SRCS) $(GEN_IMP_SRCS),$(eval $(call OBJ_template,$(file))))

$(GEN_IMP_SRCS): .genimpsources

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

infcover.o: $(top_srcdir)zlib.h $(top_srcdir)zconf.h

infcover$(EXE): infcover.o $(STATICLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ infcover.o $(STATICLIB)

cover: infcover$(EXE)
	rm -f *.gcda
	./infcover$(EXE)
	gcov inf*.c

$(STATICLIB): $(LIB_OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

$(IMPORTLIB): $(IMP_OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

$(IMP_OBJS): zlib_imp.h .genimpsources

header.lo libinit.lo: $(srcdir)/header.S zlibver.h exports.h symbols.h .genimpsources

example.o example.lo: $(top_srcdir)zlib.h $(top_srcdir)zconf.h

example.lo: $(top_srcdir)test/example.c $(top_srcdir)zlib.h $(top_srcdir)zconf.h

minigzip.o minigzip.lo: $(top_srcdir)test/minigzip.c $(top_srcdir)zlib.h $(top_srcdir)zconf.h

example64.o: $(top_srcdir)test/example.c $(top_srcdir)zlib.h $(top_srcdir)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_STATIC -D_FILE_OFFSET_BITS=64 -c -o $@ $<

example64.lo: $(top_srcdir)test/example.c $(top_srcdir)zlib.h $(top_srcdir)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -D_FILE_OFFSET_BITS=64 -c -o $@ $(top_srcdir)test/example.c

minigzip64.o: $(top_srcdir)test/minigzip.c $(top_srcdir)zlib.h $(top_srcdir)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -DZLIB_STATIC -D_FILE_OFFSET_BITS=64 -c -o $@ $<

minigzip64.lo: $(top_srcdir)test/minigzip.c $(top_srcdir)zlib.h $(top_srcdir)zconf.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(EXTRA_CFLAGS) -D_FILE_OFFSET_BITS=64 -c -o $@ $<



# slbexec.S must also be compilabe by pure-c, so we cannot preprocess it
# figure out the symbol prefix here
USER_LABEL_PREFIX := $(shell echo '__USER_LABEL_PREFIX__' | $(CROSS_PREFIX)gcc -E -P - 2>/dev/null)
ASFLAGS = -D_BasPag=$(USER_LABEL_PREFIX)_base -Wa,--register-prefix-optional
slbexec.o: slbexec.S
	$(CC) $(CFLAGS) $(CPPFLAGS) $(ASFLAGS) -c -o $@ $<


header.lo: $(srcdir)/header.S
	$(CC) $(CFLAGS) $(SFLAGS) $(CPPFLAGS) -DSHAREDLIB=\"$(SHAREDLIB)\" -c -o $@ $<

zlibver.h: $(top_srcdir)zlib.h
	grep ZLIB_VERNUM $< > $@

zlibinit.lo: $(srcdir)/zlibinit.c
	$(CC) $(CFLAGS) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<

zlibslb.lo: $(srcdir)/zlibslb.c
	$(CC) $(CFLAGS) $(SFLAGS) $(CPPFLAGS) -c -o $@ $<



$(SHAREDTARGET): $(PIC_OBJS) $(STATICLIB)
	$(LDSHARED) $(SFLAGS) $(CPPFLAGS) -o $@ $(PIC_OBJS) $(LDSHAREDLIBC) $(LDFLAGS) $(EXTRA_LDFLAGS)
	$(CROSS_PREFIX)stripex $@

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
	install -m 644 $(top_srcdir)zlib.3 $(DESTDIR)$(man3dir)
	rm -f $(DESTDIR)$(pkgconfigdir)/zlib.pc
	install -m 644 zlib.pc $(DESTDIR)$(pkgconfigdir)
# The ranlib in install is needed on NeXTSTEP which checks file times

install: install-libs
	-@if [ ! -d $(DESTDIR)$(includedir)   ]; then mkdir -p $(DESTDIR)$(includedir); fi
	-@if [ ! -d $(DESTDIR)$(includedir)/slb   ]; then mkdir -p $(DESTDIR)$(includedir)/slb; fi
	rm -f $(DESTDIR)$(includedir)/zlib.h $(DESTDIR)$(includedir)/zconf.h $(DESTDIR)$(includedir)/slb/zlib.h
	install -m 644 $(top_srcdir)zlib.h $(top_srcdir)zconf.h $(DESTDIR)$(includedir)
	install -m 644 slb/zlib.h $(DESTDIR)$(includedir)/slb

zlib.pc: Makefile
	@( \
	 VERSION=`sed -n -e '/VERSION "/s/.*"\(.*\)".*/\1/p' ${top_srcdir}zlib.h`; \
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

zlib.3.pdf: $(top_srcdir)zlib.3
	groff -mandoc -f H -T ps $(top_srcdir)zlib.3 | ps2pdf - $@

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
	install -m 644 $(top_srcdir)zlib.h $(top_srcdir)zconf.h $(DESTDIR)/purec/include
	install -m 644 slb/zlib.h $(DESTDIR)/purec/include/slb
	cd $(DESTDIR)/purec/include && cr2nl -R -d .
	install -m 644 $(PUREC)/000/zlib.lib $(PUREC)/000/zlibslb.lib $(DESTDIR)/purec/lib/000
	install -m 644 $(PUREC)/020/zlib.lib $(PUREC)/020/zlibslb.lib $(DESTDIR)/purec/lib/020
	install -d $(DESTDIR)/gfa
	install -m 644 gfa/minilib.inl $(GFA_INL) $(GFA_OTHER) $(DESTDIR)/gfa
	$(MAKE) clean
	install -m 644 READ_SLB.txt $(DESTDIR)
	VERSION=`sed -n -e '/VERSION "/s/.*"\(.*\)".*/\1/p' $(top_srcdir)zlib.h | tr -d .`; cd $(DESTDIR)/..; rm -f zlib$${VERSION}.zip; zip -r zlib$${VERSION}.zip `basename $(DESTDIR)`
	cd $(top_srcdir); VERSION=`sed -n -e '/VERSION "/s/.*"\(.*\)".*/\1/p' zlib.h`; git archive --prefix=zlib-$${VERSION}-slb/ HEAD | bzip2 > $(DESTDIR)/../zlib-$${VERSION}-slb.tar.bz2

mostlyclean: clean
clean:
	rm -f *.o *.lo *~ zlib.pc \
	   $(GEN_IMP_SRCS) \
	   example$(EXE) minigzip$(EXE) examplesh$(EXE) minigzipsh$(EXE) \
	   example64$(EXE) minigzip64$(EXE) infcover$(EXE) \
	   $(STATICLIB) $(IMPORTLIB) $(SHAREDTARGET) $(SHAREDLIBV) $(SHAREDLIBM) \
	   libz.* foo.gz so_locations \
	   maketree contrib/infback9/*.o \
	   .genimpsources
	rm -f *.gcda *.gcno *.gcov
	rm -f contrib/infback9/*.gcda contrib/infback9/*.gcno contrib/infback9/*.gcov

maintainer-clean: distclean
distclean: clean zconf docs
	rm -f zlib.pc configure.log
	-@rm -f .DS_Store
	@if [ ! -f zlib.3 ]; then rm -f zlib.3.pdf ; fi
	rm -f zlibver.h

tags:
	etags $(top_srcdir)*.[ch]

headerpc.s: header.S exports.h symbols.h zlibver.h Makefile
	$(CPP) $(CPPFLAGS) -U__USER_LABEL_PREFIX__ -D__USER_LABEL_PREFIX__= $< | sed -e 's/;/\n /g' -e 's/%//g' -e 's/jbra/jmp/' -e 's/SHAREDLIB/"$(SHAREDLIB)"/' > $@

zlibinit.lo: exports.h zlibslb.h zlibstr.h
header.lo: exports.h symbols.h zlibver.h
