/**
 * Copyright (C) 2013 Daniel Rasband.
 */

#ifndef __LIBHANGUL_T13N_H__
#define __LIBHANGUL_T13N_H__

#include <stdlib.h>

/**
 * The different types of transliteration systems available.
 */
typedef enum {
    YALE,
    REVISED_ROMANIZATION,
    MCCUNE_REISCHAUER,
    KONTSEVICH,
    SKATS
} T13N_SYSTEM;

/**
 * Convert Hangul text to other transliteration systems.
 *
 * Returns the buffer size needed to write to dest.
 */
int hangul_t13n_transliterate(char* dest, size_t buffer_size, const char* orig, T13N_SYSTEM system);

/**
 * Convert roman - or other - text to Hangul.
 *
 * Returns the buffer size needed to write to dest.
 */
int hangul_t13n_hangulize(char* dest, size_t buffer_size, const char* orig, T13N_SYSTEM system);

#endif
