/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_utf8_h__
#define __hangeul_romaja_utf8_h__

#include <stdbool.h>
#include "types.h"

int utf8_to_ucs(ucschar *dest, size_t size, const char *orig);
int ucs_to_utf8(char *dest, size_t size, const ucschar *orig);

int ucs_hangeul_choseong_index(ucschar c);
int ucs_hangeul_jungseong_index(ucschar c);
int ucs_hangeul_jongseong_index(ucschar c);
bool ucs_is_hangeul(ucschar c);

#endif
