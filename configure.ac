AC_INIT(iec16022, 0.2.3, stefan@datenfreihafen.org)
AM_INIT_AUTOMAKE([subdir-objects])
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(config.h)

dnl
dnl Require programs
dnl
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LIBTOOL

dnl
dnl Required headers
dnl
AC_HEADER_STDC

dnl
dnl Checks for typedefs, structures, and compiler characteristics.
dnl
AC_HEADER_TIME

AC_CHECK_LIB([popt], [main])
AC_CHECK_LIB([z], [main])

dnl Output the files
AC_OUTPUT([
Makefile
test/Makefile
])
