/**
 * Copyright 2012 Daniel C. Rasband.
 */
/* Standard Library */
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* Local includes */
#include "hangeul-romaja.h"
#include "types.h"
#include "parser.h"
#include "ipa.h"
#include "mccune_reischauer.h"
#include "revised_romanization.h"
#include "yale.h"
#include "yale_original.h"

/* Declarations */
int hangeul_puts(const Hangeul *hangeul);
size_t hangeul_snprint(char *dest, const Hangeul *hangeul, size_t size);
size_t hangeul_strlen(const Hangeul *hangeul);
int romaja_puts(const Romaja *romaja);
size_t romaja_snprint(char *dest, const Romaja *romaja, size_t size);
size_t romaja_strlen(const Romaja *romaja);

size_t
hangeul_to_yale(char *romaja, const char *hangeul, size_t size)
{
    size_t chars_left = 0;
    Hangeul *h = NULL;
    Romaja *r = NULL;

    /* Parse hangeul string into manageable chunks */
    hangeul_parse_str(&h, 0, hangeul);

    /* Convert to romaja in manageable chunks */
    _hangeul_to_yale(&r, h);

    /* Copy string to romaja var */
    chars_left = romaja_snprint(romaja, r, size);
    printf("romaja: %s\n", romaja);
    printf("chars_left: %lu\n", chars_left);

    hangeul_destroy(&h);
    romaja_destroy(&r);

    return chars_left;
}

size_t
hangeul_to_yale_original(char *romaja, const char *hangeul, size_t size)
{

}

size_t
hangeul_to_mccune_reischauer(char *romaja, const char *hangeul, size_t size)
{

}

size_t
hangeul_to_revised(char *romaja, const char *hangeul, size_t size)
{

}

int
hangeul_puts(const Hangeul* hangeul)
{
    int success = 0;
    return success;
}

size_t
hangeul_snprint(char *dest, const Hangeul* hangeul, size_t size)
{
    size_t chars_not_printed = 0;
    return chars_not_printed;
}

int
romaja_puts(const Romaja* romaja)
{
    int success = 0;
    char out[romaja_strlen(romaja) + 1];
    romaja_snprint(out, romaja, (romaja_strlen(romaja) + 1) * sizeof *out);
    success = puts(out);
    return success;
}

size_t
romaja_snprint(char *dest, const Romaja* romaja, size_t size)
{
    int i, len = romaja_len(romaja);
    size_t needed_length = 0;
    char tmp[len][32];
    Romaja *current = (Romaja *)romaja;

    if (size == 0) {
        return romaja_strlen(romaja);
    }
    else {
        memset(dest, 0, size);
    }

    /* Prints backwards, by syllable. */
    for (i = 0; i < len; i++) {
        if (current->syllable_type == HANGEUL) {
            if (strlen(current->initial) > 0) {
                assert(sizeof(tmp[i]) - strlen(tmp[i]) - 1 >= strlen(current->initial));
                strncat(tmp[i], current->initial, sizeof(tmp[i]) - strlen(tmp[i]) - 1);
            }

            if (strlen(current->vowel) > 0) {
                assert(sizeof(tmp[i]) - strlen(tmp[i]) - 1 >= strlen(current->vowel));
                strncat(tmp[i], current->vowel, sizeof(tmp[i]) - strlen(tmp[i]) - 1);
            }

            if (strlen(current->final) > 0) {
                assert(sizeof(tmp[i]) - strlen(tmp[i]) - 1 >= strlen(current->final));
                strncat(tmp[i], current->final, sizeof(tmp[i]) - strlen(tmp[i]) - 1);
            }
        }
        else {
            assert(sizeof(tmp[i]) - strlen(tmp[i]) - 1 >= strlen(current->combined));
            strncat(tmp[i], current->combined, sizeof(tmp[i]) - strlen(tmp[i]) - 1);
        }

        printf("tmp[%d]: %s; strlen(tmp[%d]): %lu\n", i, tmp[i], i, strlen(tmp[i]));
        needed_length += strlen(tmp[i]);
        current = current->next;
    }

    for (i = len - 1; size - strlen(dest) - 1 > strlen(tmp[i]); i--) {
        printf("i: %d; size: %lu; strlen(dest): %lu; strlen(tmp[i]): %lu\n", i, size, strlen(dest), strlen(tmp[i]));
        assert(size - strlen(dest) - 1 > strlen(tmp[i]));
        strncat(dest, tmp[i], size - strlen(dest) - 1);
    }

    return needed_length - size;
}

size_t
hangeul_strlen(const Hangeul* hangeul)
{
    size_t length = 0;
    const Hangeul *current = hangeul;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

size_t
romaja_strlen(const Romaja *romaja)
{
    size_t len = 0;
    Romaja *current = (Romaja *)romaja;

    while (current != NULL) {
        if (current->syllable_type == HANGEUL) {
            if (current->initial != NULL) {
                len += strlen(current->initial);
                printf("initial: %s\n", current->initial);
            }
            if (current->vowel != NULL) {
                len += strlen(current->vowel);
                printf("vowel: %s\n", current->vowel);
            }
            if (current->final != NULL) {
                len += strlen(current->final);
                printf("final: %s\n", current->final);
            }
        }
        else {
            len += strlen(current->combined);
            printf("combined: %s\n", current->combined);
        }

        current = current->next;
    }

    return len;
}
