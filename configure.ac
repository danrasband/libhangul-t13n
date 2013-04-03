# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.61])
AC_INIT([libhangul-t13n], [0.0.0], [danrasband@gmail.com])

# Libtool
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# Automake
AM_INIT_AUTOMAKE([1.10 no-define])

# Gettext
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18.1])

# Source dir's unique file
AC_CONFIG_SRCDIR([src/hangulconv.c])

# Config header
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([getopt.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile po/Makefile.in])
AC_OUTPUT([src/Makefile])
AC_OUTPUT
