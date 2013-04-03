PACKAGE = @PACKAGE@
DEFS = -DLOCALEDIR=\"$(localedir)\" -DPACKAGE=\"$(package)\"

# libhtr library
lib_LTLIBRARIES = libhtr.la
libhtr_la_SOURCES = libhtr.c hangul.c romaja.c \
  mccune-reischauer.c revised-romanization.c skats.c yale.c
include_HEADERS = libhtr.h

# Command-line tool
bin_PROGRAMS = hangulconv
hangulconv_SOURCES = hangulconv.c
hangulconv_LDADD = libhtr.la $(LTLIBINTL)
