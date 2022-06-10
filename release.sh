#!/bin/sh
VER=$(grep AC_INIT configure.ac | sed -e 's/.*,\[\(.*\)\],.*/\1/')
if ! grep -q "^$VER$" NEWS ; then
    echo "Please add NEWS entry for version $VER!"
    exit 1
fi
if ! grep -q "^$(date --iso-8601=date)" NEWS ; then
    echo "Expect today's date in NEWS!"
    exit 1
fi
rm -f "iec16022-$VER.tar.xz" "iec16022-$VER.tar.xz.asc"
make distclean
./autogen.sh
make dist
gpg -a --detach-sign iec16022-$VER.tar.xz
git tag -s v${VER}
rm -rf .libs
rm -f iec16022.signed.exe
./winbuild.sh
strip .libs/iec16022.exe
make iec16022.signed.exe
cp iec16022.signed.exe iec16022-$VER.exe
