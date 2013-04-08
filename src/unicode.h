
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

/* UTF8 byte masks */
#define UTF8_FOUR_BYTE_MASK     0xf0    // 11110xxx
#define UTF8_THREE_BYTE_MASK    0xe0    // 1110xxxx
#define UTF8_TWO_BYTE_MASK      0xc0    // 110xxxxx
#define UTF8_ONE_BYTE_MAX       0x7f    // 01111111

#define UTF8_IS_FOUR_BYTES(first_byte) ((first_byte & UTF8_FOUR_BYTE_MASK) == UTF8_FOUR_BYTE_MASK)
#define UTF8_IS_THREE_BYTES(first_byte) ((first_byte & UTF8_THREE_BYTE_MASK) == UTF8_THREE_BYTE_MASK) \
  && !UTF8_IS_FOUR_BYTES(first_byte)
#define UTF8_IS_TWO_BYTES(first_byte) ((first_byte & UTF8_TWO_BYTE_MASK) == UTF8_TWO_BYTE_MASK) \
  && !UTF8_IS_THREE_BYTES(first_byte)
#define UTF8_IS_ONE_BYTE(first_byte) first_byte < UTF8_ONE_BYTE_MAX

/* Struct to hold a utf8 character set */
typedef struct {
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;
} utf8_char_bytes;

/**
 * Convert utf8 character to unicode code point.
 */
ucschar utf8_to_ucs(const utf8_char_bytes *bytes);

#endif
