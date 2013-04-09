AM_CFLAGS = -I$(top_builddir)/src

TESTS = utf8_to_ucs_test
check_PROGRAMS = utf8_to_ucs_test
utf8_to_ucs_test_SOURCES = utf8_to_ucs_test.c $(top_builddir)/src/unicode.c

TESTS += euckr_to_utf8_test
check_PROGRAMS += euckr_to_utf8_test
euckr_to_utf8_test_SOURCES = euckr_to_utf8_test.c $(top_builddir)/src/encoding.c $(top_builddir)/src/xmalloc.c
euckr_to_utf8_test_LDADD = $(LTLIBINTL) $(LTLIBICONV)

