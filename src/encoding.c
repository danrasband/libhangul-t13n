/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "encoding.h"

/*
UCS to UTF8
U-00000000 – U-0000007F: 0xxxxxxx
U-00000080 – U-000007FF: 110xxxxx 10xxxxxx
U-00000800 – U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
U-00010000 – U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
U-00200000 – U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
U-04000000 – U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

typedef enum utf8CharType {
    ONE_BYTE,
    TWO_BYTES,
    THREE_BYTES,
    FOUR_BYTES,
    FIVE_BYTES,
    SIX_BYTES,
    SUB_BYTE
} utf8CharType;

#define UTF8_ONE_BYTE_MASK      0
#define UTF8_ONE_BYTE_UCS       0
#define IS_ONE_BYTE_UTF8(byte)  (UTF8_ONE_BYTE_MASK & byte) == UTF8_ONE_BYTE_MASK
#define UTF8_TWO_BYTE_MASK      0xC0 /* 0b11000000 */
#define UTF8_TWO_BYTE_UCS       0x80
#define IS_TWO_BYTE_UTF8(byte)  (UTF8_TWO_BYTE_MASK & byte) == UTF8_TWO_BYTE_MASK
#define UTF8_THREE_BYTE_MASK    0xE0 /* 0b11100000 */
#define UTF8_THREE_BYTE_UCS     0x00000800
#define IS_THREE_BYTE_UTF8(byte) (UTF8_THREE_BYTE_MASK & byte) == UTF8_THREE_BYTE_MASK
#define UTF8_FOUR_BYTE_MASK     0xF0 /* 0b11110000 */
#define UTF8_FOUR_BYTE_UCS      0x00010000
#define IS_FOUR_BYTE_UTF8(byte) (UTF8_FOUR_BYTE_MASK & byte) == UTF8_FOUR_BYTE_MASK
#define UTF8_FIVE_BYTE_MASK     0xF8 /* 0b11111000 */
#define UTF8_FIVE_BYTE_UCS      0x00200000
#define IS_FIVE_BYTE_UTF8(byte) (UTF8_FIVE_BYTE_MASK & byte) == UTF8_FIVE_BYTE_MASK
#define UTF8_SIX_BYTE_MASK      0xFC /* 0b11111100 */
#define UTF8_SIX_BYTE_UCS       0x04000000
#define IS_SIX_BYTE_UTF8(byte)  (UTF8_SIX_BYTE_MASK & byte) == UTF8_SIX_BYTE_MASK

#define UTF8_SUB_BYTE_MASK              0x80 /* 0b10000000 */
#define UTF8_TWO_BYTE_FIRST_SUB_BYTE    0x80
#define UTF8_THREE_BYTE_FIRST_SUB_BYTE  0xa0 /* 0x80 | (0x80 >> 2) */
#define UTF8_FOUR_BYTE_FIRST_SUB_BYTE   0x90 /* 0x80 | (0x80 >> 3) */
#define UTF8_FIVE_BYTE_FIRST_SUB_BYTE   0x88 /* 0x80 | (0x80 >> 4) */
#define UTF8_SIX_BYTE_FIRST_SUB_BYTE    0x84 /* 0x80 | (0x80 >> 5) */

#define UTF8_FIRST_BYTE_START   0xC0
#define UTF8_FIRST_BYTE_END     0xFD
#define UTF8_SUB_BYTE_START     0x80
#define UTF8_SUB_BYTE_END       0xBF

#define UTF8_MAX_BYTES 6

#define UTF8_MASK_MATCH(MASK, byte) ((MASK & byte) == MASK)

int
utf8_to_ucs(ucschar *dest, size_t size, const char *orig)
{
    int i;
    int len = strlen(orig);
    int returnValue = 0;
    bool is_last = false;

    utf8char z, y, x, w, v, u;
    ucschar *ucs_str = (ucschar *)malloc(strlen(orig) * sizeof(ucschar));
    int ucs_str_index = 0;

    /* Loop through each byte */
    for (i = 0; i < len;) {
        z = (ucschar)orig[i++];
        printf("%x\n", z);

        if (UTF8_MASK_MATCH(UTF8_SIX_BYTE_MASK, z)) {
            assert(i <= len - 5);
            if (i >= len - 5) break;

            y = (ucschar)orig[i++];
            x = (ucschar)orig[i++];
            w = (ucschar)orig[i++];
            v = (ucschar)orig[i++];
            u = (ucschar)orig[i++];

            ucs_str[ucs_str_index++] = ((z - UTF8_SIX_BYTE_MASK) * pow(64, 5))
                + ((y - 0x80) * pow(64, 4))
                + ((x - 0x80) * pow(64, 3))
                + ((w - 0x80) * pow(64, 2))
                + ((v - 0x80) * 64)
                + (u - 0x80);
        }
        else if (UTF8_MASK_MATCH(UTF8_FIVE_BYTE_MASK, z)) {
            assert(i <= len - 4);
            if (i >= len - 4) break;

            y = (ucschar)orig[i++];
            x = (ucschar)orig[i++];
            w = (ucschar)orig[i++];
            v = (ucschar)orig[i++];

            ucs_str[ucs_str_index++] = ((z - UTF8_FIVE_BYTE_MASK) * pow(64, 4))
                + ((y - 0x80) * pow(64, 3))
                + ((x - 0x80) * pow(64, 2))
                + ((w - 0x80) * 64)
                + (v - 0x80);
        }
        else if (UTF8_MASK_MATCH(UTF8_FOUR_BYTE_MASK, z)) {
            assert(i <= len - 3);
            if (i >= len - 3) break;

            y = (ucschar)orig[i++];
            x = (ucschar)orig[i++];
            w = (ucschar)orig[i++];

            ucs_str[ucs_str_index++] = ((z - UTF8_FOUR_BYTE_MASK) * pow(64, 3))
                + ((y - 0x80) * pow(64, 2))
                + ((x - 0x80) * 64)
                + (w - 0x80);
        }
        else if (UTF8_MASK_MATCH(UTF8_THREE_BYTE_MASK, z)) {
            assert(i <= len - 2);
            if (i > len - 2) break;

            y = (ucschar)orig[i++];
            x = (ucschar)orig[i++];

            ucs_str[ucs_str_index++] = ((z - UTF8_THREE_BYTE_MASK) * pow(64, 2))
                + ((y - 0x80) * 64)
                + (x - 0x80);
        }
        else if (UTF8_MASK_MATCH(UTF8_TWO_BYTE_MASK, z)) {
            assert(i < len - 1);
            if (i > len - 1) break;

            y = (ucschar)orig[i++];

            ucs_str[ucs_str_index++] = ((z - UTF8_TWO_BYTE_MASK) * 64)
                + (y - 0x80);
        }
        else if (UTF8_MASK_MATCH(UTF8_ONE_BYTE_MASK, z)) {
            assert(i < len);
            if (i > len) break;

            ucs_str[ucs_str_index++] = z;
        }
        else {
            assert(false);
        }
    }

    memcpy(dest, ucs_str, size);

    returnValue = ucs_strlen(ucs_str) - size;

    free(ucs_str);
    return returnValue;
}

int
ucs_to_utf8(char *dest, size_t size, const ucschar *orig)
{

}

ucschar
ucs_hangeul_choseong(ucschar c)
{

}

ucschar
ucs_hangeul_jungseong(ucschar c)
{

}

ucschar
ucs_hangeul_jongseong(ucschar c)
{

}

bool
ucs_is_hangeul(ucschar c)
{

}
