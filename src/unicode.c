/**
 * Copyright (C) 2013 Daniel Rasband
 */

#include "unicode.h"
#include <string.h>
#include <stdio.h>

/* UTF8 to Unicode conversion helpers. */
#define UCS_FOUR_BYTE_START     0x10000
#define UCS_THREE_BYTE_START    0x0800
#define UCS_TWO_BYTE_START      0x0080

// 4-byte
#define UTF8_4BYTE_BYTE1_START  0xf0    // 11110000
#define UTF8_4BYTE_BYTE2_START  0X90    // 10010000

// 3-byte
#define UTF8_3BYTE_BYTE1_START  0xe0    // 11100000
#define UTF8_3BYTE_BYTE2_START  0xa0    // 10100000

// 2-byte
#define UTF8_2BYTE_BYTE1_START  0xc2    // 11000010

// Global
#define UTF8_SUB_BYTE_START     0x80    // All subbytes start with 10xxxxxx
#define UTF8_SUB_BYTE_FACTOR    0x40    // 0x80 to 0xbf
#define UTF8_SUB_BYTE_END       0xc0    // 0x80 to 0xbf (0xc0 become 0x80)

int utf8_byte_length(uint8_t first_byte);

/**
 * Convert utf8 to unicode code points.
 */
ucschar
utf8_to_ucs(const utf8_char_bytes *bytes)
{
    ucschar tmpchar;
    utf8char b1 = bytes->byte1;
    utf8char b2 = bytes->byte2;
    utf8char b3 = bytes->byte3;
    utf8char b4 = bytes->byte4;

    // 4-byte UTF8 char.
    if (UTF8_IS_FOUR_BYTES(b1)) {
        tmpchar = UCS_FOUR_BYTE_START;
        if ((b1 - UTF8_4BYTE_BYTE1_START) >= 1) {
            tmpchar += (UTF8_SUB_BYTE_END - UTF8_4BYTE_BYTE2_START) * UTF8_SUB_BYTE_FACTOR * UTF8_SUB_BYTE_FACTOR;
            tmpchar += (b1 - UTF8_4BYTE_BYTE1_START - 1) * ((UTF8_SUB_BYTE_END - UTF8_SUB_BYTE_START) * UTF8_SUB_BYTE_FACTOR * UTF8_SUB_BYTE_FACTOR);
            tmpchar += (b2 - UTF8_SUB_BYTE_START) * UTF8_SUB_BYTE_FACTOR * UTF8_SUB_BYTE_FACTOR;
        } else {
            tmpchar += (b2 - UTF8_4BYTE_BYTE2_START) * UTF8_SUB_BYTE_FACTOR * UTF8_SUB_BYTE_FACTOR;
        }
        tmpchar += (b3 - UTF8_SUB_BYTE_START) * UTF8_SUB_BYTE_FACTOR;
        tmpchar += b4 - UTF8_SUB_BYTE_START;
    }
    // 3-byte UTF8 char.
    else if (UTF8_IS_THREE_BYTES(b1)) {
        tmpchar = UCS_THREE_BYTE_START;
        if ((b1 - UTF8_3BYTE_BYTE1_START) >= 1) {
            tmpchar += (UTF8_SUB_BYTE_END - UTF8_3BYTE_BYTE2_START) * UTF8_SUB_BYTE_FACTOR;
            tmpchar += (b1 - UTF8_3BYTE_BYTE1_START - 1) * ((UTF8_SUB_BYTE_END - UTF8_SUB_BYTE_START) * UTF8_SUB_BYTE_FACTOR);
            tmpchar += (b2 - UTF8_SUB_BYTE_START) * UTF8_SUB_BYTE_FACTOR;
        } else {
            tmpchar += (b2 - UTF8_3BYTE_BYTE2_START) * UTF8_SUB_BYTE_FACTOR;
        }
        tmpchar += b3 - UTF8_SUB_BYTE_START;
    }
    // 2-byte UTF8 char.
    else if (UTF8_IS_TWO_BYTES(b1)) {
        tmpchar = UCS_TWO_BYTE_START;
        tmpchar += (b1 - UTF8_2BYTE_BYTE1_START) * UTF8_SUB_BYTE_FACTOR;
        tmpchar += b2 - UTF8_SUB_BYTE_START;
    }
    // 1-byte UTF8 char.
    else if (UTF8_IS_ONE_BYTE(b1)) {
        tmpchar = b1;
    }

    return tmpchar;
}

int
get_ucschar(const char *utf8_str, ucschar *dest)
{
    utf8_char_bytes bytes;
    size_t len = strlen(utf8_str);
    *dest = 0;

    if (len == '\0') {
        return 0;
    }

    bytes.byte1 = utf8_str[0];
    if (len > 1) {
        bytes.byte2 = utf8_str[1];
    }
    if (len > 2) {
        bytes.byte3 = utf8_str[2];
    }
    if (len > 3) {
        bytes.byte4 = utf8_str[3];
    }

    *dest = utf8_to_ucs(&bytes);

}

int
utf8_byte_length(uint8_t first_byte)
{
    if (UTF8_IS_FOUR_BYTES(first_byte))
        return 4;
    if (UTF8_IS_THREE_BYTES(first_byte))
        return 3;
    if (UTF8_IS_TWO_BYTES(first_byte))
        return 2;
    return 1;
}
