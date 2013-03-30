# libhangeulromaja library
lib_LTLIBRARIES = libhangeul-romaja.la
libhangeul_romaja_la_SOURCES = libhangeul-romaja.c
include_HEADERS = libhangeul-romaja.h

# Command-line tool
bin_PROGRAMS = hangeulconv
hangeulconv_SOURCES = hangeulconv.c progname.c
hangeulconv_LDADD = libhangeul-romaja.la

