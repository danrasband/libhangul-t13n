/**
 * Copyright (C) 2013 Daniel Rasband.
 */

#include "common.h"
#include "libhangul-t13n.h"
#include "unicode.h"
#include "hangul.h"
#include "yale.h"
#include "mccune-reischauer.h"
#include "revised-romanization.h"
#include "skats.h"
#include "kontsevich.h"

int
hangul_t13n_transliterate(char* dest, size_t buffer_size, const char* orig, T13N_SYSTEM system)
{
    ucschar c;
    int buffer_needed = 0;
    UTF8_STRING_HANDLER *handler = utf8_open(orig);

    /* START TESTING */
    buffer_needed = strlen(orig);
    strncpy(dest, orig, buffer_size);
    if (buffer_size > 0)
        dest[buffer_size - 1] = '\0';
    /* END TESTING */

    while ((c = get_ucschar(handler)) != (ucschar)EOF) {

    }

    utf8_close(handler);

    return buffer_needed;
}

int
hangul_t13n_hangulize(char* dest, size_t buffer_size, const char* orig, T13N_SYSTEM system)
{
    int buffer_needed = 0;

    buffer_needed = strlen(orig);

    strncpy(dest, orig, buffer_size);

    if (buffer_size > 0)
        dest[buffer_size - 1] = '\0';

    return buffer_needed;
}
