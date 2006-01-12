CC=/usr/bin/cc
INSTALL=/usr/bin/install
GZIP=/bin/gzip

DESTDIR=/usr/local

bindir=$(DESTDIR)/bin
mandir=$(DESTDIR)/share/man

CFLAGS=-Wall

all: iec16022 manpage

iec16022: iec16022ecc200.o image.o iec16022.c
	$(CC) -c iec16022.c
	$(CC) -o iec16022 $(CFLAGS) reedsol.o iec16022.o image.o iec16022ecc200.o -lz -lpopt

manpage: iec16022.1
	$(GZIP) -f --best < iec16022.1 > iec16022.1.gz

install: all
	$(INSTALL) -m 755 iec16022 $(bindir)
	$(INSTALL) -m 644 iec16022.1.gz $(mandir)/man1

iec16022ecc200.o: iec16022ecc200.c iec16022ecc200.h reedsol.o
	$(CC) -c iec16022ecc200.c

image.o: image.c image.h
	$(CC) -c image.c

reedsol.o: reedsol.c reedsol.h
	$(CC)  -DLIB -c reedsol.c

clean:
	rm -f iec16022 iec16022.1.gz *.o
