/**
 * Copyright 2012 Daniel C. Rasband.
 */
/* Standard Library */
#include <string.h>
#include <stdio.h>

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
int hangeul_puts(const Hangeul* hangeul);
int hangeul_snprint(char *dest, size_t size, const Hangeul* hangeul);
int hangeul_strlen(const Hangeul *hangeul);
int romaja_strlen(const Romaja *romaja);

int
hangeul_to_yale(char *romaja, size_t size, const char *hangeul)
{
    int chars_left = 0;
    Hangeul *h = NULL;
    Romaja *r = NULL;

    /* Parse hangeul string into manageable chunks */
    hangeul_parse_str(&h, 0, hangeul);

    /* Convert to romaja in manageable chunks */
    _hangeul_to_yale(&r, h);

    /* Copy string to romaja var */
    chars_left = romaja_snprint(romaja, size, r);

    /*hangeul_destroy(h);
    romaja_destroy(r);*/

    return chars_left;
}

int
hangeul_to_yale_original(char *romaja, size_t size, const char *hangeul)
{

}

int
hangeul_to_mccune_reischauer(char *romaja, size_t size, const char *hangeul)
{

}

int
hangeul_to_revised(char *romaja, size_t size, const char *hangeul)
{

}

int
hangeul_puts(const Hangeul* sentence)
{
    int success = 0;
    return success;
}

int
hangeul_snprint(char *dest, size_t size, const Hangeul* sentence)
{
    int chars_not_printed = 0;
    return chars_not_printed;
}

int
romaja_puts(const Romaja* sentence)
{
    int success = 0;
    char out[romaja_strlen(sentence) + 1];
    romaja_snprint(out, sizeof(out), sentence);
    success = puts(out);
    return success;
}

int
romaja_snprint(char *dest, size_t size, const Romaja* romaja)
{
    if (size == 0) {
        return romaja_strlen(romaja);
    }

    return romaja_strlen(romaja) - strlen(dest);
}

int
hangeul_strlen(const Hangeul* hangeul)
{
    int length = 0;
    const Hangeul *current = hangeul;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

int
romaja_strlen(const Romaja *romaja)
{
    int len = 0;
    //Romaja *current = malloc(sizeof(Romaja));
    // *current = *romaja;

    /*while (current != NULL) {
        if (current->syllable_type == HANGEUL) {
            if (current->initial != NULL) {
                len += sizeof(current->initial);
            }
            if (current->vowel != NULL) {
                len += sizeof(current->vowel);
            }
            if (current->final != NULL) {
                len += sizeof(current->final);
            }
        }
        else {
            if (current->nonhangeul) {
                len += sizeof(current->nonhangeul);
            }
        }
        current = sentence->next;
    }

    romaja_destroy(current);
     */

    return len;
}
