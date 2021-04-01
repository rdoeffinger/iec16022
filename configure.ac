AC_INIT([iec16022],[0.3.0],[Reimar.Doeffinger@gmx.de])
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

PKG_CHECK_MODULES([POPT], [popt], ,
AC_CHECK_LIB([popt], [main], POPT_LIBS=-lpopt,AC_MSG_ERROR([Missing library: popt not found.]))
)
# zlib is rather useless for our purpose
# AC_CHECK_LIB([z], [main],,AC_MSG_ERROR([Missing library: zlib not found.]))

dnl Output the files
AC_CONFIG_FILES([
Makefile
test/Makefile
libiec16022.pc
iec16022.1
])
AC_OUTPUT
