/**
 *
 */

#include "../src/unicode.h"
#include <stdio.h>

int
main()
{
    ucschar ucs_c;

    utf8_char_bytes oneByteChar    =   { 0x6f };
    utf8_char_bytes twoByteChar    =   { 0xd8, 0xb3 };
    utf8_char_bytes threeByteChar  =   { 0xe3, 0x85, 0xa5 };
    utf8_char_bytes fourByteChar   =   { 0xf0, 0x90, 0xa4, 0xa6 };
    utf8_char_bytes fourByteChar2  =   { 0xf3, 0xa0, 0x81, 0xb8 };

    ucs_c = utf8_to_ucs (&oneByteChar);
    if (ucs_c != 0x6f)
        return 1;

    ucs_c = utf8_to_ucs (&twoByteChar);
    if (ucs_c != 0x633)
        return 1;

    ucs_c = utf8_to_ucs (&threeByteChar);
    if (ucs_c != 0x3165)
        return 1;

    ucs_c = utf8_to_ucs (&fourByteChar);
    if (ucs_c != 0x10926)
        return 1;

    ucs_c = utf8_to_ucs (&fourByteChar2);
    if (ucs_c != 0xe0078)
        return 1;

    return 0;
}
