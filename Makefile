CC=cc

all:
	$(CC) -o iec16022 iec16022.c -DLIB image.c reedsol.c iec16022ecc200.c -lz -lpopt

clean:	
	rm -f iec16022
