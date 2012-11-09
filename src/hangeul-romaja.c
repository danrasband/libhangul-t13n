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
    Romaja *current = (Romaja *)romaja;

    if (size == 0) {
        return romaja_strlen(romaja);
    }

    /* Must set dest to nulls so that concatenation will work properly. */
    memset(dest, 0, size);

    /* Prints by syllable. */
    for (i = 0; i < len; i++) {
        /*printf("%s\n", dest);
        printf("size: %lu; strlen(dest): %lu; strlen(current->combined): %lu\n", size, strlen(dest), strlen(current->combined));*/
        assert(size - strlen(dest) > strlen(current->combined));
        strncat(dest, current->combined, size - strlen(dest) - 1);

        needed_length += strlen(current->combined);
        current = current->next;
    }

    if (needed_length + 1 > size) {
        return needed_length + 1 - size;
    }
    return 0;
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
        len += strlen(current->combined);

        current = current->next;
    }

    return len;
}
