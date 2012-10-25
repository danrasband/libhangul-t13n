/**
 * Copyright 2012 Daniel C. Rasband.
 */
/* Standard Library */
#include <string.h>
#include <stdio.h>

/* Local includes */
#include "hangeul-romaja.h"
#include "types.h"
#include "ipa.h"
#include "mccune_reischauer.h"
#include "revised_romanization.h"
#include "yale.h"
#include "yale_original.h"

/* Declarations */
int hangeul_parse_str(Hangeul **hangeulRef, const char *source);
int hangeul_puts(const Hangeul* hangeul);
int hangeul_snprint(char *dest, size_t size, const Hangeul* hangeul);
int hangeul_strlen(const Hangeul *hangeul);
int romaja_parse_str(Romaja **romajaRef, const char *source);
int romaja_strlen(const Romaja *romaja);
void hangeul_push(Hangeul **hangeul, ucschar combined);
void romaja_push(Romaja **romaja, ucschar initial[4], ucschar vowel[4], ucschar final[4], ucschar nonhangeul, ucschar combined, SyllableType syllable_type);

int
hangeul_to_yale(char *romaja, size_t size, const char *hangeul)
{
    int chars_left = 0;
    Hangeul *h = NULL;
    Romaja *r = NULL;

    /* Parse hangeul string into manageable chunks */
    hangeul_parse_str(&h, hangeul);

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
hangeul_parse_str(Hangeul** hangeulRef, const char *source)
{
    int success = 0;
    int i = 0;
    char next = source[i];
    char hangeul[3];

    while ((next = source[i]) != '\0') {
        if (next > )
        i++;
    }

    return success;
}

int
romaja_parse_str(Romaja** sentenceRef, const char *source)
{
    int success = 0;
    return success;
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
    return 0;
}

int
romaja_strlen(const Romaja *romaja)
{
    int len = 0;
    Romaja *current = malloc(sizeof(Romaja));
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
    }*/

    romaja_destroy(current);

    return len;
}

void
hangeul_push(Hangeul **hangeul, ucschar combined)
{
    /* Parse combined character into nonhangeul or choseong, jungseong,
    jongseong */

}

void
romaja_push(Romaja **romaja, ucschar initial[4], ucschar vowel[4], ucschar final[4], ucschar nonhangeul, ucschar combined, SyllableType syllable_type)
{
    /* Add to most recent syllable or create new syllable to add to. */

}

int
hangeul_destroy(Hangeul **hangeulRef)
{
    Hangeul *current = *hangeulRef;
    Hangeul *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *hangeulRef = NULL;
}

int
romaja_destroy(Romaja **romajaRef)
{
    Romaja *current = *romajaRef;
    Romaja *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *romajaRef = NULL;
}

ucschar
_hangeul_get_choseong(ucschar combined)
{

}

ucschar
_hangeul_get_jungseong(ucschar combined)
{

}

ucschar
_hangeul_get_jongseong(ucschar combined)
{

}

