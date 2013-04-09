TESTS = utf8_to_ucs_test euckr_to_utf8_test
check_PROGRAMS = utf8_to_ucs_test euckr_to_utf8_test

utf8_to_ucs_test_SOURCES = utf8_to_ucs_test.c $(top_builddir)/src/unicode.c

euckr_to_utf8_test_SOURCES = euckr_to_utf8_test.c $(top_builddir)/src/encoding.c $(top_builddir)/src/xmalloc.c
euckr_to_utf8_test_LDADD = $(LTLIBINTL) $(LTLIBICONV)

