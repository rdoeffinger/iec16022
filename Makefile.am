SUBDIRS = test

lib_LTLIBRARIES = libiec16022.la

libiec16022include_HEADERS =	\
	iec16022ecc200.h		\
	image.h				\
	reedsol.h

libiec16022includedir = $(includedir)/iec16022

libiec16022_la_LDFLAGS = -version-number $(LT_VERSION_C):$(LT_VERSION_R):$(LT_VERSION_A)

bin_PROGRAMS = iec16022

man_MANS = iec16022.1

iec16022_SOURCES =	\
	iec16022.c

iec16022_LDADD =	\
	libiec16022.la

libiec16022_la_SOURCES =	\
	iec16022ecc200.c	\
	iec16022ecc200.h	\
	image.c			\
	image.h			\
	reedsol.c		\
	reedsol.h

EXTRA_DIST = 				\
	libiec16022.pc.in		\
	test/testsuite.sh 		\
	test/testsuite-example.bin	\
	test/testsuite-example.eps	\
	test/testsuite-example.hex	\
	test/testsuite-example.png	\
	test/testsuite-example.text	\
	$(man_MANS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA= libiec16022.pc
