/**
 *
 */

#include "../src/unicode.h"
#include <stdio.h>

int
main()
{
    int char_len;
    ucschar ucs_c;

    char *oneByteChar    =   { 0x6f, '\0' };
    char *twoByteChar    =   { 0xd8, 0xb3, '\0' };
    char *threeByteChar  =   { 0xe3, 0x85, 0xa5, '\0' };
    char *fourByteChar   =   { 0xf0, 0x90, 0xa4, 0xa6, '\0' };
    char *fourByteChar2  =   { 0xf3, 0xa0, 0x81, 0xb8, '\0' };

    char_len = get_ucschar(oneByteChar, &ucs_c);
    if (ucs_c != 0x6f || char_len != 1)
        return 1;

    char_len = get_ucschar (twoByteChar, &ucs_c);
    if (ucs_c != 0x633 || char_len != 2)
        return 1;

    char_len = get_ucschar (threeByteChar, &ucs_c);
    if (ucs_c != 0x3165, || char_len != 3)
        return 1;

    char_len = get_ucschar (fourByteChar, &ucs_c);
    if (ucs_c != 0x10926 || char_len != 4)
        return 1;

    char_len = get_ucschar (fourByteChar2, &ucs_c);
    if (ucs_c != 0xe0078 || char_len != 4)
        return 1;

    return 0;
}
