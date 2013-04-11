/**
 * Copyright (C) 2013 Daniel Rasband.
 */

#include <config.h>
#include <stdio.h>
#include "macros.h"
#include "unicode.h"

int
main()
{
    int i = 0;
    ucschar ucs_c;
    UTF8_STRING_HANDLER *str_handler;

    utf8char utf8_str[] = {
        0x6f, // one byte char
        0xd8, 0xb3, // two byte char
        0xe3, 0x85, 0xa5, // three byte char
        0xf0, 0x90, 0xa4, 0xa6, // four byte char
        0xf3, 0xa0, 0x81, 0xb8, // five byte char
        '\0' // end of string
    };

    ucschar ucs_str[] = {
        0x6f,
        0x633,
        0x3165,
        0x10926,
        0xe0078,
        '\0'
    };

    str_handler = utf8_open(utf8_str);

    while ((ucs_c = get_ucschar(str_handler)) != (ucschar)EOF) {
        ASSERT(ucs_c == ucs_str[i]);
        i++;
    }

    utf8_close(str_handler);
    return PASS;
}
