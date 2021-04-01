#!/bin/sh
set -x

libtoolize --force || glibtoolize --force
aclocal
autoheader
automake --add-missing
autoconf configure.ac > configure
chmod +x configure
./configure
