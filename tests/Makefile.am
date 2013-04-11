AM_CFLAGS = -I$(top_builddir)/src

TESTS = \
  utf8_to_ucs_test              \
  euckr_to_utf8_test            \
  ucschar_to_utf8char_str_test  \
  yale_test                     \
  revised_romanization_test     \
  mccune_reischauer_test        \
  skats_test                    \
  kontsevich_test

check_PROGRAMS = \
  utf8_to_ucs_test              \
  euckr_to_utf8_test            \
  ucschar_to_utf8char_str_test  \
  yale_test                     \
  revised_romanization_test     \
  mccune_reischauer_test        \
  skats_test                    \
  kontsevich_test

LIBS = \
  $(top_builddir)/src/libhangul-t13n.la \
  $(LTLIBINTL)                          \
  $(LTLIBICONV)

utf8_to_ucs_test_SOURCES =      \
  utf8_to_ucs_test.c            \
  $(top_builddir)/src/unicode.c \
  $(top_builddir)/src/xmalloc.c

euckr_to_utf8_test_SOURCES =      \
  euckr_to_utf8_test.c            \
  $(top_builddir)/src/encoding.c  \
  $(top_builddir)/src/xmalloc.c

euckr_to_utf8_test_LDADD = @LIBS@

ucschar_to_utf8char_str_test_SOURCES = \
  ucschar_to_utf8char_str_test.c  \
  $(top_builddir)/src/unicode.c   \
  $(top_builddir)/src/xmalloc.c

ucschar_to_utf8char_str_test_LDADD = @LIBS@

yale_test_SOURCES = yale_test.c
yale_test_LDADD = @LIBS@

revised_romanization_test_SOURCES = revised_romanization_test.c
revised_romanization_test_LDADD = @LIBS@

mccune_reischauer_test_SOURCES = mccune_reischauer_test.c
mccune_reischauer_test_LDADD = @LIBS@

skats_test_SOURCES = skats_test.c
skats_test_LDADD = $(top_builddir)/src/libhangul-t13n.la

kontsevich_test_SOURCES = kontsevich_test.c
kontsevich_test_LDADD = @LIBS@
