#!/bin/sh
VER=$(grep AC_INIT configure.ac | sed -e 's/.*, \(.*\),.*/\1/')
if ! grep -q "^$VER$" NEWS ; then
    echo "Please add NEWS entry for version $VER!"
    exit 1
fi
if ! grep -q "^$(date --iso-8601=date)" NEWS ; then
    echo "Expect today's date in NEWS!"
    exit 1
fi
git tag -s v${VER}
./winbuild.sh
make iec16022.signed.exe
cp iec16022.signed.exe iec16022-$VER.exe
