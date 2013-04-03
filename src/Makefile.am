PACKAGE = @PACKAGE@
DEFS = -DLOCALEDIR=\"$(localedir)\" -DPACKAGE=\"$(package)\"

# libhangeulromaja library
lib_LTLIBRARIES = libhangeul-romaja.la
libhangeul_romaja_la_SOURCES = libhangeul-romaja.c hangeul.c romaja.c \
  mccune-reischauer.c revised-romanization.c skats.c yale.c
include_HEADERS = libhangeul-romaja.h

# Command-line tool
bin_PROGRAMS = hangeulconv
hangeulconv_SOURCES = hangeulconv.c
hangeulconv_LDADD = libhangeul-romaja.la $(LTLIBINTL)
