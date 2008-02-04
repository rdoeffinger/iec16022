#!/bin/sh
set -x

aclocal
libtoolize --force
autoheader
automake --add-missing
autoconf configure.ac > configure
chmod +x configure
