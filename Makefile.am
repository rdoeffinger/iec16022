SUBDIRS = test

noinst_LTLIBRARIES = libiec16022ecc200.la
noinst_HEADERS =	\
	image.h			\
	reedsol.h

bin_PROGRAMS = iec16022

man_MANS = iec16022.1

iec16022_SOURCES =	\
	iec16022.c

iec16022_LDADD =	\
	libiec16022ecc200.la

libiec16022ecc200_la_SOURCES =	\
	iec16022ecc200.c \
	iec16022ecc200.h \
	image.c			\
	image.h			\
	reedsol.c		\
	reedsol.h

EXTRA_DIST = test/testsuite.sh \
			 test/testsuite-example.bin \
			 test/testsuite-example.eps \
			 test/testsuite-example.hex \
			 test/testsuite-example.png \
			 test/testsuite-example.text \
			 $(man_MANS)
