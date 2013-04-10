/**
 * Copyright (C) 2013 Daniel Rasband
 */

#include "unicode.h"
#include <string.h>
#include <stdio.h>

/* UTF8 byte masks */
#define UTF8_FOUR_BYTE_MASK     0xf0    // 11110xxx
#define UTF8_THREE_BYTE_MASK    0xe0    // 1110xxxx
#define UTF8_TWO_BYTE_MASK      0xc0    // 110xxxxx
#define UTF8_ONE_BYTE_MAX       0x7f    // 01111111

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

// Macros for byte size
#define UTF8_IS_FOUR_BYTES(first_byte) ((first_byte & UTF8_FOUR_BYTE_MASK) == UTF8_FOUR_BYTE_MASK)
#define UTF8_IS_THREE_BYTES(first_byte) ((first_byte & UTF8_THREE_BYTE_MASK) == UTF8_THREE_BYTE_MASK) \
    && !UTF8_IS_FOUR_BYTES(first_byte)
#define UTF8_IS_TWO_BYTES(first_byte) ((first_byte & UTF8_TWO_BYTE_MASK) == UTF8_TWO_BYTE_MASK) \
    && !UTF8_IS_THREE_BYTES(first_byte)
#define UTF8_IS_ONE_BYTE(first_byte) first_byte < UTF8_ONE_BYTE_MAX

/**
 * Pointer to current position in UTF-8 string.
 */
struct utf8_string_handler {
    utf8char *start;
    utf8char *current;
    utf8char *end;
};

int utf8_byte_length(utf8char first_byte);

/**
 * Convert utf8 to unicode code points.
 */
ucschar
utf8_to_ucs(utf8char b1, utf8char b2, utf8char b3, utf8char b4)
{
    ucschar tmpchar;

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

UTF8_STRING_HANDLER *
utf8_open(const char *str)
{
    UTF8_STRING_HANDLER *handler = malloc(sizeof(UTF8_STRING_HANDLER));
    handler->start = (utf8char *)str;
    handler->current = (utf8char *)str;
    handler->end = (utf8char *)(str + strlen(str));
    return handler;
}

void
utf8_close(UTF8_STRING_HANDLER *handler)
{
    free(handler);
}

ucschar
get_ucschar(UTF8_STRING_HANDLER *handler)
{
    int byte_length;
    utf8char b1 = 0, b2 = 0, b3 = 0, b4 = 0;
    if (handler == NULL || handler->current == handler->end)
        return (ucschar)-1;

    byte_length = utf8_byte_length(handler->current[0]);
    switch (byte_length) {
    case 4:
        b4 = handler->current[3];
    case 3:
        b3 = handler->current[2];
    case 2:
        b2 = handler->current[1];
    case 1:
        b1 = handler->current[0];
    }

    handler->current += byte_length;

    return utf8_to_ucs(b1, b2, b3, b4);
}

int
utf8_byte_length(utf8char first_byte)
{
    if (UTF8_IS_FOUR_BYTES(first_byte))
        return 4;
    if (UTF8_IS_THREE_BYTES(first_byte))
        return 3;
    if (UTF8_IS_TWO_BYTES(first_byte))
        return 2;
    return 1;
}
