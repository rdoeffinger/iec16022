CC=/usr/bin/cc
INSTALL=/usr/bin/install

all:
	$(CC) -o iec16022 iec16022.c -DLIB image.c reedsol.c iec16022ecc200.c -lz -lpopt

install: all
	$(INSTALL) -m 755 iec16022 /usr/bin


clean:	
	rm -f iec16022
