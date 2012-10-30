/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
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

#define UTF8_ONE_BYTE_MASK      0b00000000
#define UTF8_ONE_BYTE_UCS       0x00000000
#define IS_ONE_BYTE_UTF8(byte)  (UTF8_ONE_BYTE_MASK & byte) == UTF8_ONE_BYTE_MASK
#define UTF8_TWO_BYTE_MASK      0b11000000
#define UTF8_TWO_BYTE_UCS       0x00000080
#define IS_TWO_BYTE_UTF8(byte)  (UTF8_TWO_BYTE_MASK & byte) == UTF8_TWO_BYTE_MASK
#define UTF8_THREE_BYTE_MASK    0b11100000
#define UTF8_THREE_BYTE_UCS     0x00000800
#define IS_THREE_BYTE_UTF8(byte) (UTF8_THREE_BYTE_MASK & byte) == UTF8_THREE_BYTE_MASK
#define UTF8_FOUR_BYTE_MASK     0b11110000
#define UTF8_FOUR_BYTE_UCS      0x00010000
#define IS_FOUR_BYTE_UTF8(byte) (UTF8_FOUR_BYTE_MASK & byte) == UTF8_FOUR_BYTE_MASK
#define UTF8_FIVE_BYTE_MASK     0b11111000
#define UTF8_FIVE_BYTE_UCS      0x00200000
#define IS_FIVE_BYTE_UTF8(byte) (UTF8_FIVE_BYTE_MASK & byte) == UTF8_FIVE_BYTE_MASK
#define UTF8_SIX_BYTE_MASK      0b11111100
#define UTF8_SIX_BYTE_UCS       0x04000000
#define IS_SIX_BYTE_UTF8(byte)  (UTF8_SIX_BYTE_MASK & byte) == UTF8_SIX_BYTE_MASK
#define UTF8_SUB_BYTE_MASK      0x10000000

#define UTF8_FIRST_BYTE_START   0xC0
#define UTF8_FIRST_BYTE_END     0xFD
#define UTF8_SUB_BYTE_START     0x80
#define UTF8_SUB_BYTE_END       0xBF

#define UTF8_MAX_BYTES 6

#define IS_LAST_BYTE(groupType, length) (ONE_BYTE && length >= 1 || \
    TWO_BYTES && length >= 2 || \
    THREE_BYTES && length >= 3 || \
    FOUR_BYTES && length >= 4 || \
    FIVE_BYTES && length >= 5 || \
    SIX_BYTES && length >= 6)

/* Declarations */
size_t utf8_strlen(const utf8char *str);
size_t ucs_strlen(const ucschar *str);
ucschar parse_utf8_str(size_t length, utf8char sequence[]);
ucschar utf8_ucs_start_value(utf8char byte);
ucschar utf8_ucs_sub_value(utf8char byte);

int
utf8_to_ucs(ucschar *dest, size_t size, const char *orig)
{
    assert(sizeof(dest) >= size);
    int i;
    int len = strlen(orig);
    bool is_last = false;
    utf8char current;
    utf8char tmp[UTF8_MAX_BYTES];
    utf8CharType charType = ONE_BYTE;
    utf8CharType charGroupType = ONE_BYTE;
    ucschar *ucs_str = (ucschar *)malloc(strlen(orig) * sizeof(ucschar));

    /* Loop through each byte */
    for (i = 0; i < len; i++) {
        is_last = false;
        current = orig[i];
        if (utf8_strlen(tmp) == 0) {
            if ((UTF8_ONE_BYTE_MASK & current) == UTF8_ONE_BYTE_MASK) {
                charType = ONE_BYTE;
            }
            else if ((UTF8_TWO_BYTE_MASK & current) == UTF8_TWO_BYTE_MASK) {
                charType = TWO_BYTES;
                charGroupType = TWO_BYTES;
            }
            else if ((UTF8_THREE_BYTE_MASK & current) == UTF8_THREE_BYTE_MASK) {
                charType = THREE_BYTES;
                charGroupType = THREE_BYTES;
            }
            else if ((UTF8_FOUR_BYTE_MASK & current) == UTF8_FOUR_BYTE_MASK) {
                charType = FOUR_BYTES;
                charGroupType = FOUR_BYTES;
            }
            else if ((UTF8_FIVE_BYTE_MASK & current) == UTF8_FIVE_BYTE_MASK) {
                charType = FIVE_BYTES;
                charGroupType = FIVE_BYTES;
            }
            else if ((UTF8_SIX_BYTE_MASK & current) == UTF8_SIX_BYTE_MASK) {
                charType = SIX_BYTES;
                charGroupType = SIX_BYTES;
            }
            else if ((UTF8_SUB_BYTE_MASK & current) == UTF8_SUB_BYTE_MASK) {
                charType = SUB_BYTE;
            }
        }

        switch (charType) {
            case ONE_BYTE:
                assert(utf8_strlen(tmp) == 0);
                tmp[0] = current;
                is_last = true;
                break;
            case TWO_BYTES:
                tmp[0] = current;
                break;
            case THREE_BYTES:
                tmp[0] = current;
                break;
            case FOUR_BYTES:
                tmp[0] = current;
                break;
            case FIVE_BYTES:
                tmp[0] = current;
                break;
            case SIX_BYTES:
                tmp[0] = current;
                break;
            case SUB_BYTE:
                tmp[utf8_strlen(tmp)] = current;
                if (IS_LAST_BYTE(charGroupType, utf8_strlen(tmp))) {
                    is_last = true;
                }
                break;
        }

        if (is_last) {
            ucs_str[(int)ucs_strlen(ucs_str)] = parse_utf8_str(utf8_strlen(tmp), tmp);
            memset(tmp, 0, UTF8_MAX_BYTES * sizeof(utf8char));
            is_last = false;
        }
    }

    ucs_str = realloc(ucs_str, ucs_strlen(ucs_str) * sizeof(ucschar) + sizeof(ucschar));

    memcpy(dest, ucs_str, size);

    return ucs_strlen(ucs_str) - ucs_strlen(dest);
}

int
ucs_to_utf8(char *dest, size_t size, const ucschar *orig)
{

}


/* Get the UCS integer for the utf8 sequence */
ucschar
parse_utf8_str(size_t length, utf8char sequence[])
{
    int i;
    assert(length <= 6 && length <= utf8_strlen(sequence));
    ucschar value = 0;

    for (i = 0; i < length; i++) {
        if (i == 0) {
            value = utf8_ucs_start_value(sequence[i]);
        }
        else {
            value += utf8_ucs_sub_value(sequence[i]);
        }
    }
}

ucschar
utf8_ucs_start_value(utf8char byte)
{
    ucschar result = 0;
    if (IS_TWO_BYTE_UTF8(byte)) {
        result = UTF8_TWO_BYTE_UCS + (byte - (UTF8_TWO_BYTE_MASK | UTF8_FIRST_BYTE_START));
    }
    else if (IS_THREE_BYTE_UTF8(byte)) {
        result = UTF8_THREE_BYTE_UCS + (byte - (UTF8_THREE_BYTE_MASK | UTF8_FIRST_BYTE_START));
    }
    else if (IS_FOUR_BYTE_UTF8(byte)) {
        result = UTF8_FOUR_BYTE_UCS + (byte - (UTF8_FOUR_BYTE_MASK | UTF8_FIRST_BYTE_START));
    }
    else if (IS_FIVE_BYTE_UTF8(byte)) {
        result = UTF8_FIVE_BYTE_UCS + (byte - (UTF8_FIVE_BYTE_MASK | UTF8_FIRST_BYTE_START));
    }
    else if (IS_SIX_BYTE_UTF8(byte)) {
        result = UTF8_SIX_BYTE_UCS + (byte - (UTF8_SIX_BYTE_MASK | UTF8_FIRST_BYTE_START));
    }
    return result;
}

ucschar
utf8_ucs_sub_value(utf8char byte)
{
    assert((UTF8_SUB_BYTE_MASK & byte) == UTF8_SUB_BYTE_MASK);
    assert((byte & ~UTF8_SUB_BYTE_MASK) >= UTF8_SUB_BYTE_START && (byte & ~UTF8_SUB_BYTE_MASK) <= UTF8_SUB_BYTE_END);
    ucschar result = 0;

    result = byte - (UTF8_SUB_BYTE_MASK | UTF8_SUB_BYTE_START);

    return result;
}

ucschar
ucs_hangeul_choseong(ucschar c)
{

}

ucschar
ucs_hangeul_jungseong(ucschar c)
{

}

ucschar ucs_hangeul_jongseong(ucschar c)
{

}

ucschar ucs_is_hangeul(ucschar c)
{

}
