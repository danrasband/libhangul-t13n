/**
 * Copyright (C) 2013 Daniel Rasband.
 */

#ifndef __UNICODE_H__
#define __UNICODE_H__

#include <stdint.h>
#include <stdlib.h>
#include "xmalloc.h"

/**
 * Unicode/UTF8 helpers.
 *
 * ucschar is a Unicode character point. It has to be 2 bytes to handle up to
 * 0xFFFF.
 */
typedef uint32_t ucschar;
typedef uint8_t utf8char;

typedef struct utf8_string_handler UTF8_STRING_HANDLER;

/**
 * Convert first UTF-8 character to unicode code point.
 */
ucschar get_ucschar(UTF8_STRING_HANDLER *handler);

/**
 * Convert a unicode code point to a UTF8 character (a string of 1 to 4 bytes).
 */
utf8char *ucschar_to_utf8char_str(ucschar c);

/**
 * Prepare a UTF8_STRING_HANDLER.
 */
UTF8_STRING_HANDLER *utf8_open(const char *str);

/**
 * Close the UTF8_STRING_HANDLER, freeing memory, etc.
 */
void utf8_close(UTF8_STRING_HANDLER *handler);

#endif
