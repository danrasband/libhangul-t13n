PACKAGE = @PACKAGE@
DEFS = -DLOCALEDIR=\"$(localedir)\" -DPACKAGE=\"$(package)\"

# libhangul-t13n library
lib_LTLIBRARIES = libhangul-t13n.la

libhangul_t13n_la_SOURCES = \
  libhangul-t13n.c          \
  hangul.c                  \
  mccune-reischauer.c       \
  revised-romanization.c    \
  skats.c                   \
  yale.c                    \
  xmalloc.c                 \
  unicode.c

include_HEADERS = libhangul-t13n.h

# Command-line tool
bin_PROGRAMS = hangulconv
hangulconv_SOURCES = hangulconv.c encoding.c
# Uncomment when using valgrind.
# hangulconv_LDFLAGS = -no-install
hangulconv_LDADD = libhangul-t13n.la $(LTLIBINTL) $(LTLIBICONV)
