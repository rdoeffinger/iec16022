AM_CFLAGS = -Bsymbolic -Wundef -Wall -Wno-switch -Wno-parentheses -Wpointer-arith -Wredundant-decls -Werror=format-security -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wdisabled-optimization -Wno-pointer-sign -Wdeclaration-after-statement -Werror-implicit-function-declaration -std=c99 -D_POSIX_C_SOURCE=200112 -D_ISOC99_SOURCE -Wl,--as-needed -Wl,--no-undefined -fno-asynchronous-unwind-tables

image.lo: AM_CFLAGS += -Wno-unused-result

SUBDIRS = . test

lib_LTLIBRARIES = libiec16022.la

libiec16022include_HEADERS =	\
	iec16022ecc200.h		\
	image.h				\
	reedsol.h

libiec16022includedir = $(includedir)/iec16022

libiec16022_la_LDFLAGS = -version-number $(LT_VERSION_C):$(LT_VERSION_R):$(LT_VERSION_A)

bin_PROGRAMS = iec16022
check_PROGRAMS = iec16022
EXTRA_PROGRAMS = fuzzer

man_MANS = iec16022.1

iec16022_SOURCES =	\
	iec16022.c

iec16022_LDADD =	\
	libiec16022.la  \
	-lpopt

fuzzer_SOURCES = fuzzer.c
fuzzer_LDADD = $(iec16022_LDADD)

libiec16022_la_SOURCES =	\
	iec16022ecc200.c	\
	iec16022ecc200.h	\
	image.c			\
	image.h			\
	reedsol.c		\
	reedsol.h

EXTRA_DIST =				\
	autogen.sh			\
	autogen-clean.sh		\
	iec16022.1.in			\
	libiec16022.pc.in		\
	test/testsuite.sh		\
	test/testsuite-example.bin	\
	test/testsuite-example.eps	\
	test/testsuite-example.hex	\
	test/testsuite-example.png	\
	test/testsuite-example.text	\
	test/testsuite-example.utf8	\
	$(man_MANS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA= libiec16022.pc

iec16022.signed.exe: iec16022.exe
	osslsigncode sign -ts http://timestamp.globalsign.com/scripts/timestamp.dll -certs $(SIGNKEY).crt -key $(SIGNKEY).key -in $^ -out $@
