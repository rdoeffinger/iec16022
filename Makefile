CC=/usr/bin/cc
INSTALL=/usr/bin/install
GZIP=/bin/gzip

DESTDIR=/usr/local

prefix=$(DESTDIR)
bindir=$(prefix)/bin
mandir=$(prefix)/share/man

all:
	$(CC) -o iec16022 iec16022.c -DLIB image.c reedsol.c iec16022ecc200.c -lz -lpopt
	$(GZIP) -f --best < iec16022.1 > iec16022.1.gz

install: all
	$(INSTALL) -m 755 iec16022 $(bindir)
	$(INSTALL) -m 644 iec16022.1.gz $(mandir)/man1


clean:
	rm -f iec16022
	rm -f iec16022.1.gz
