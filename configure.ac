AC_INIT([iec16022],[0.3.1],[Reimar.Doeffinger@gmx.de])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([subdir-objects no-dist-gzip dist-xz])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE

AC_CONFIG_HEADERS([config.h])


dnl
dnl LIB API versioning
dnl
dnl From the libtool manual:
dnl 1. Start with version information of `0:0:0' for each libtool library.
dnl 2. Update the version information only immediately before a public release.
dnl    More frequent updates are unnecessary, and only guarantee that the current
dnl    interface number gets larger faster.
dnl 3. If the library source code has changed at all since the last update, then increment
dnl    revision (`c:r:a' becomes `c:r+1:a').
dnl 4. If any interfaces have been added, removed, or changed since the last update,
dnl    increment current, and set revision to 0.
dnl 5. If any interfaces have been added since the last public release, then increment age.
dnl 6. If any interfaces have been removed since the last public release, then set age
dnl    to 0.
LT_VERSION_C=0
LT_VERSION_R=1
LT_VERSION_A=0

AC_SUBST(LT_VERSION_C)
AC_SUBST(LT_VERSION_R)
AC_SUBST(LT_VERSION_A)


dnl
dnl Require programs
dnl
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
LT_INIT

# add fallback if pkg-config is not installed
m4_ifdef([PKG_CHECK_MODULES],,[define(PKG_CHECK_MODULES, $4)])
PKG_CHECK_MODULES([POPT], [popt], ,
AC_SEARCH_LIBS([poptGetContext], [popt], POPT_LIBS=-lpopt,AC_MSG_ERROR([Missing library: popt not found.]))
)
# zlib is rather useless for our purpose
# AC_CHECK_LIB([z], [main],,AC_MSG_ERROR([Missing library: zlib not found.]))

ac_orig_ldflags="$LDFLAGS"
LDFLAGS="$LDFLAGS -Wl,--as-needed -Wl,--no-undefined"
AC_LINK_IFELSE([AC_LANG_SOURCE([int main() { return 0; }])], [], [LDFLAGS="$ac_orig_ldflags"])

dnl Output the files
AC_CONFIG_FILES([
Makefile
test/Makefile
libiec16022.pc
iec16022.1
])
AC_OUTPUT
