# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.61])
AC_INIT([libhangul-t13n], [0.0.0], [danrasband@gmail.com])

# Libtool
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# Automake
AM_INIT_AUTOMAKE([1.10 no-define])

# Gettext
GETTEXT_PACKAGE="$PACKAGE"
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [gettext package name])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18])
AM_ICONV

# Source dir's unique file
AC_CONFIG_SRCDIR([src/hangulconv.c])

# Config header
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CC_C99
AC_PROG_LIBTOOL
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([stdbool.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([getopt.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
])
AC_OUTPUT
