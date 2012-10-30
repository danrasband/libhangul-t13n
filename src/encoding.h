/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_utf8_h__
#define __hangeul_romaja_utf8_h__

#include "types.h"

int utf8_to_ucs(ucschar *dest, size_t size, const char *orig);
int ucs_to_utf8(char *dest, size_t size, const ucschar *orig);

ucschar ucs_hangeul_choseong(ucschar c);
ucschar ucs_hangeul_jungseong(ucschar c);
ucschar ucs_hangeul_jongseong(ucschar c);
ucschar ucs_is_hangeul(ucschar c);

#endif
