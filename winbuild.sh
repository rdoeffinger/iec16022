make clean
CFLAGS="-O2 -I$HOME/mxe/usr/i686-w64-mingw32/include" LDFLAGS="-L$HOME/mxe/usr/i686-w64-mingw32/lib -Wl,--nxcompat -Wl,--no-seh -Wl,--dynamicbase" ./configure  --host=i686-w64-mingw32
make -j6
