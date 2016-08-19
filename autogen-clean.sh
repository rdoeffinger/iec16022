#!/bin/sh

if [ -f Makefile ]; then
	echo "Making make distclean..."
	make distclean
fi

echo "Removing autogenned files..."
rm -rf autom4te.cache config.guess config.sub configure install-sh missing mkinstalldirs Makefile.in m4 ltmain.sh stamp-h.in */Makefile.in ltconfig stamp-h config.h.in aclocal.m4 depcomp
echo "Done."
