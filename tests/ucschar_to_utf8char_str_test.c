/**
 * Copyright (C) 2013 Daniel Rasband.
 */

#include <stdio.h>
#include <string.h>
#include "macros.h"
#include "unicode.h"

#ifndef NARRAY
#define NARRAY(ary) sizeof(ary)/sizeof(ary[0])
#endif

int
main()
{
    int i;
    utf8char *tmp_str = NULL;

    ucschar unicode_points[] = {
        0x00,       // One byte start
        0x7f,       // One byte end
        0x80,       // Two byte start
        0x7ff,      // Two byte end
        0x800,      // Three byte start
        0xa0f3,     // Three byte middle
        0xffff,     // Three byte end
        0x10000,    // Four byte start
        0x10fca7     // Four byte near end
    };

    utf8char utf8_char_str[][5] = {
        { 0x00, '\0' },
        { 0x7f, '\0' },
        { 0xc2, 0x80, '\0' },
        { 0xdf, 0xbf, '\0' },
        { 0xe0, 0xa0, 0x80, '\0' },
        { 0xea, 0x83, 0xb3, '\0' },
        { 0xef, 0xbf, 0xbf, '\0' },
        { 0xf0, 0x90, 0x80, 0x80, '\0' },
        { 0xf4, 0x8f, 0xb2, 0xa7, '\0' }
    };

    for (i = 0; i < NARRAY(unicode_points); i++) {
        tmp_str = ucschar_to_utf8char_str(unicode_points[i]);

        ASSERT((0 == strncmp(tmp_str, utf8_char_str[i], 4)));

        free(tmp_str);
        tmp_str = NULL;
    }

    return PASS;
}

