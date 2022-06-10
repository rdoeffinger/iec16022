# Last build using popt from
# https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-popt-1.16-1-any.pkg.tar.xz
# https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-gettext-0.21-3-any.pkg.tar.zst
# https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-libiconv-1.17-1-any.pkg.tar.zst
# add -lintl -liconv to mingw32/lib/pkgconfig/popt.pc
make clean
make distclean
PKG_CONFIG_PATH=mingw32/lib/pkgconfig CFLAGS="-O2 -Imingw32/include" LDFLAGS="--static -Lmingw32/lib -Wl,--nxcompat -Wl,--no-seh -Wl,--dynamicbase" ./configure  --host=i686-w64-mingw32
make -j6
